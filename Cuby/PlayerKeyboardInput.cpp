#include "PlayerKeyboardInput.h"
#include <allegro5\allegro5.h>
#include "Debug.h"
#include "TTTBoard.h"

CPlayerKeyboardInput::CPlayerKeyboardInput(CPlayer* player, CTTTBoard* m_board)
	: IInputComponent("Player Keyboard Input")
	, m_player(player)
	, m_board(m_board)
{
	assert(m_player != nullptr);
	assert(m_board != nullptr);
}

CPlayerKeyboardInput::~CPlayerKeyboardInput(void)
{

}

void CPlayerKeyboardInput::Handle(const ALLEGRO_EVENT& ev)
{
	// We only want keyboard events.
	if (ev.type < ALLEGRO_EVENT_KEY_DOWN || ev.type > ALLEGRO_EVENT_KEY_UP)
		return;

	if (ev.keyboard.keycode == ALLEGRO_KEY_PAD_7)
		m_board->Move(0,0, m_player);
	else if (ev.keyboard.keycode == ALLEGRO_KEY_PAD_8)
		m_board->Move(0, 1, m_player);
	else if (ev.keyboard.keycode == ALLEGRO_KEY_PAD_9)
		m_board->Move(0, 2, m_player);
	else if (ev.keyboard.keycode == ALLEGRO_KEY_PAD_4)
		m_board->Move(1, 0, m_player);
	else if (ev.keyboard.keycode == ALLEGRO_KEY_PAD_5)
		m_board->Move(1, 1, m_player);
	else if (ev.keyboard.keycode == ALLEGRO_KEY_PAD_6)
		m_board->Move(1, 2, m_player);
	else if (ev.keyboard.keycode == ALLEGRO_KEY_PAD_1)
		m_board->Move(2, 0, m_player);
	else if (ev.keyboard.keycode == ALLEGRO_KEY_PAD_2)
		m_board->Move(2, 1, m_player);
	else if (ev.keyboard.keycode == ALLEGRO_KEY_PAD_3)
		m_board->Move(2, 2, m_player);
}