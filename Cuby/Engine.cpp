#include "Engine.h"
#include "Component.h"
#include "GameBoard.h"
#include "Renderer.h"
#include "InputComponent.h"
#include <algorithm>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>

CEngine::CEngine(void)
	: m_done(false)
	, m_needRedraw(true)
	, m_display(nullptr)
	, m_timer(nullptr)
	, m_evQ(nullptr)
	, m_renderer(nullptr)
	, m_timeLastUpdated(0)
	, m_gameBoard(nullptr)
{

}

CEngine::~CEngine(void)
{
	al_destroy_event_queue(m_evQ);
	m_evQ = nullptr;
	al_destroy_timer(m_timer);
	m_timer = nullptr;
	al_destroy_display(m_display);
	m_display = nullptr;
}

int CEngine::Init(void)
{
	// Init Allegro core.
	if (!al_init())
		return -1;
	// Load/manipulate image files.
	if (!al_init_image_addon())
		return -2;
	// Ability to draw primitives.
	if (!al_init_primitives_addon())
		return -3;
	// To receive keyboard events.
	if (!al_install_keyboard())
		return -4;
	// To receive mouse events.
	if (!al_install_mouse())
		return -5;

	m_display = al_create_display(1000, 600);
	if (!m_display)
		return -10;
	m_timer = al_create_timer(1.0f / 60.0f);
	if (!m_timer)
		return -11;
	m_evQ = al_create_event_queue();
	if (!m_evQ)
		return -12;

	// Get display events.
	al_register_event_source(m_evQ, al_get_display_event_source(m_display));
	// Get timer events.
	al_register_event_source(m_evQ, al_get_timer_event_source(m_timer));
	// Get keyboard events.
	al_register_event_source(m_evQ, al_get_keyboard_event_source());
	// Get mouse events.
	al_register_event_source(m_evQ, al_get_mouse_event_source());

	// Renderer that controls what is shown on the screen.
	m_renderer = new CRenderer(this);

	return 0;
}

int CEngine::Run(void)
{
	al_start_timer(m_timer);
	
	for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); ++iter)
		(*iter)->Start();

	while(!m_done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(m_evQ, &ev);
		
		if (ev.type == ALLEGRO_EVENT_TIMER)
			Update();
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;
		else if (ev.type >= ALLEGRO_EVENT_JOYSTICK_AXIS && ev.type < ALLEGRO_EVENT_TIMER)
			PushEvent(ev);
		
		if (m_needRedraw && al_is_event_queue_empty(m_evQ))
			Render();
	}
	return EXIT_SUCCESS;
}

void CEngine::OnUpdate(void)
{
	const double ct = al_current_time();
	const double dt = ct - m_timeLastUpdated;
	m_timeLastUpdated = ct;

	if (GetGameBoard())
		GetGameBoard()->Update(dt);

	for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); ++iter)
		(*iter)->Update(dt);
	// Game objects have been updated, therefore
	// they will need to be redrawn.
	m_needRedraw = true;
}

void CEngine::OnRender(void)
{
	if (m_renderer)
		m_renderer->Render();
	al_flip_display();
	al_clear_to_color(al_map_rgb(150,150,150));
	m_needRedraw = false;
}

void CEngine::PushEvent(const ALLEGRO_EVENT& ev)
{
	for (auto iter = m_inputComponents.begin(); iter != m_inputComponents.end(); ++iter)
		if ((*iter)->IsEnabled())
			(*iter)->Handle(ev);
}

bool CEngine::AddInputComponent(IInputComponent* input)
{
	auto iter = std::find(m_inputComponents.begin(), m_inputComponents.end(), input);
	if (iter == m_inputComponents.end())
	{
		m_inputComponents.push_back(input);
		return true;
	}
	return false;
}

void CEngine::RemoveInputComponent(IInputComponent* input)
{
	m_inputComponents.remove(input);
}

bool CEngine::AddGameObject(IGameObject* gameObject)
{
	auto iter = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
	if (iter == m_gameObjects.end())
	{
		m_gameObjects.push_back(gameObject);
		return true;
	}
}

void CEngine::RemoveGameObject(IGameObject* gameObject)
{
	m_gameObjects.remove(gameObject);
}