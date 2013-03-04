#include "UI.h"
#include "MenuStrip.h"

CUI::CUI(void)
	: m_pCanvas(nullptr)
	, m_pRenderer(nullptr)
{
	m_pRenderer = new Gwen::Renderer::Allegro;

	m_skin.SetRender(m_pRenderer);
	m_skin.Init("DefaultSkin.png");

	// The fonts work differently in Allegro - it can't use
	// system fonts. So force the skin to use a local one.
	m_skin.SetDefaultFont( L"OpenSans.ttf", 11 );

	// Create a Canvas (it's root, on which all other GWEN panels are created)
	m_pCanvas = new Gwen::Controls::Canvas( &m_skin );
	m_pCanvas->SetSize( al_get_display_width(al_get_current_display()), al_get_display_height(al_get_current_display()));
	m_pCanvas->SetBackgroundColor( Gwen::Color( 150, 170, 170, 255 ) );
	m_pCanvas->SetDrawBackground(false);

	m_allegroInput.Initialize(m_pCanvas);
	//new CMenuStrip(GetCanvas(), );
}

void CUI::SetupMenus(void)
{

}

CUI::~CUI(void)
{
	delete m_pRenderer;
	m_pRenderer = nullptr;
	delete m_pCanvas;
	m_pCanvas = nullptr;
}