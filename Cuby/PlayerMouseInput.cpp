#include "PlayerMouseInput.h"
#include <allegro5\allegro5.h>
#include "TTTBoard.h"
#include "TTTBoardRender.h"

CPlayerMouseInput::CPlayerMouseInput(CPlayer* player, CTTTBoard* board)
	: m_player(player)
	, m_board(board)
{

}

void CPlayerMouseInput::Handle(const ALLEGRO_EVENT& ev)
{
	// For now, all we care about is ALLEGRO_EVENT_MOUSE_BUTTON_UP
	if (!(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && ev.mouse.button == 1))
		return;

	// Find out which piece the user clicked.
	const size_t col = (ev.mouse.x - m_board->GetX()) / m_board->GetGamePieceSize();
	const size_t row = (ev.mouse.y - m_board->GetY()) / m_board->GetGamePieceSize();
	// We don't have to worry about the use not clicking one of the pieces because
	// Move() will handle that.
	m_board->Move(row, col, m_player);
}