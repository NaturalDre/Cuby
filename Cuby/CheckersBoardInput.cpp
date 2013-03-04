#include "CheckersBoardInput.h"
#include "CheckersBoard.h"
#include <allegro5\allegro5.h>

CCheckersBoardInput::CCheckersBoardInput(CCheckersBoard* board)
	: m_board(board)
{
	assert(m_board != nullptr);
}

CCheckersBoardInput::~CCheckersBoardInput(void)
{

}

void CCheckersBoardInput::Handle(const ALLEGRO_EVENT& ev)
{
	// If the event wasn't mouse button 1 going down, we return.
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && ev.mouse.button == 1)
	{
		const size_t col = (ev.mouse.x - m_board->GetX()) / m_board->GetPieceWidth();
		const size_t row = (ev.mouse.y - m_board->GetY()) / m_board->GetPieceHeight();

		const size_t OWNER = m_board->GetPlayerAt(RowCol(row, col));
		// Do a move only if a the selected piece is valid, belongs to the current player, and
		// that it does not  belong to the current player.
		if (m_board->GetSelected().valid && m_board->GetCurPlayer() == m_board->GetPlayerAt(m_board->GetSelected())/* && OWNER != CCheckersBoard::BLANK*/ && OWNER != m_board->GetCurPlayer())
			m_board->Move(row, col);
		// In all other scenarios, select the position (row,col). Note that
		// Select() will take care of selecting an invalid piece.
		else
			m_board->Select(row, col);
	}
}