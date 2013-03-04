#include "CheckersBoardRender.h"
#include "CheckersBoard.h"
#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>

//const size_t GAMEPIECESIZE = 64;
CCheckersBoardRender::CCheckersBoardRender(CCheckersBoard* board, CRenderer* renderer)
	: IRenderComponent("Checkers Renderer", renderer)
	, m_board(board)
	, m_alphaPiece(nullptr)
	, m_alphaKingPiece(nullptr)
	, m_betaPiece(nullptr)
	, m_betaKingPiece(nullptr)
{
	m_alphaPiece = new CBitmap("Checkers/alpha.png", 0);
	m_alphaKingPiece = new CBitmap("Checkers/alphaKing.png", 0);
	m_betaPiece = new CBitmap("Checkers/beta.png", 0);
	m_betaKingPiece = new CBitmap("Checkers/betaKing.png", 0);
}

CCheckersBoardRender::~CCheckersBoardRender(void)
{

}

void CCheckersBoardRender::OnRender(void)
{
	const size_t displayWidth = al_get_display_width(al_get_current_display());
	const size_t displayHeight = al_get_display_height(al_get_current_display());
	//const size_t gamePieceSize = GAMEPIECESIZE;

	// Note: I assume 0 to be even.
	bool rowIsOdd = true;
	bool drawBlack = true;
	// First top 3 rows
	for (size_t row = 0; row < 8; ++row)
	{
		// Note: On first run(row is 0), isOdd will correctly be set to false.
		rowIsOdd = !rowIsOdd; 
		if (rowIsOdd)
			drawBlack = false;
		else
			drawBlack = true;

		for (size_t col = 0; col < m_board->GetBoard().size(); ++col)
		{
			drawBlack = !drawBlack;
			const size_t x1 = col * m_board->GetPieceWidth() + m_board->GetX();
			const size_t y1 = row * m_board->GetPieceHeight() + m_board->GetY();
			const size_t x2 = x1 + m_board->GetPieceWidth();
			const size_t y2 = y1 + m_board->GetPieceHeight();

			if (drawBlack)
				al_draw_filled_rectangle(x1,y1,x2,y2, al_map_rgb(0,0,0));
			else
				al_draw_filled_rectangle(x1,y1,x2,y2, al_map_rgb(155,0,0));


			// Draw the pieces
			const size_t PIECETYPE = m_board->GetBoard()[row][col];
			if (PIECETYPE == CCheckersBoard::BLANK)
				continue;
			else if(PIECETYPE == CCheckersBoard::ALPHA)
				al_draw_scaled_bitmap(m_alphaPiece->GetData(), 0, 0, m_alphaPiece->GetWidth(), m_alphaPiece->GetHeight(), x1, y1, m_board->GetPieceWidth(), m_board->GetPieceHeight(), 0);
			else if(PIECETYPE == CCheckersBoard::BETA)
				al_draw_scaled_bitmap(m_betaPiece->GetData(), 0, 0, m_betaPiece->GetWidth(), m_betaPiece->GetHeight(), x1, y1, m_board->GetPieceWidth(), m_board->GetPieceHeight(), 0);
			else if(PIECETYPE == CCheckersBoard::KING_ALPHA)
				al_draw_scaled_bitmap(m_alphaKingPiece->GetData(), 0, 0, m_alphaKingPiece->GetWidth(), m_alphaKingPiece->GetHeight(), x1, y1, m_board->GetPieceWidth(), m_board->GetPieceHeight(), 0);
			else if(PIECETYPE == CCheckersBoard::KING_BETA)
				al_draw_scaled_bitmap(m_betaKingPiece->GetData(), 0, 0, m_betaKingPiece->GetWidth(), m_betaKingPiece->GetHeight(), x1, y1, m_board->GetPieceWidth(), m_board->GetPieceHeight(), 0);
		}
	}

	if (m_board->GetSelected().valid)
	{
		const RowCol rc = m_board->GetSelected();
		const size_t x1 = rc.col * m_board->GetPieceWidth() + m_board->GetX();
		const size_t y1 = rc.row * m_board->GetPieceHeight() + m_board->GetY();
			const size_t x2 = x1 + m_board->GetPieceWidth();
			const size_t y2 = y1 + m_board->GetPieceHeight();

		al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(0, 255, 0), 2);
	}
}

void CCheckersBoardRender::OnStart(void)
{
	m_alphaPiece->Load();
	assert(m_alphaPiece->IsLoaded() == true);

	m_alphaKingPiece->Load();
	assert(m_alphaKingPiece->IsLoaded() == true);

	m_betaPiece->Load();
	assert(m_betaPiece->IsLoaded() == true);

	m_betaKingPiece->Load();
	assert(m_betaKingPiece->IsLoaded() == true);
}