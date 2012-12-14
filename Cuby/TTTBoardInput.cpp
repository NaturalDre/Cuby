#include "TTTBoardInput.h"
#include "Debug.h"
#include "TTTBoard.h"
#include <allegro5\allegro5.h>

void CTTTBoardInput::Handle(const ALLEGRO_EVENT& ev)
{
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		// NOTE("Board input has received a key down event.");
	}
	else if(ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		// NOTE("Board input has received a key up event.");
		if (ev.keyboard.keycode == ALLEGRO_KEY_R)
			m_board->StartNewMatch();
	}
}
