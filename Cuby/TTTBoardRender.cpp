#include "TTTBoardRender.h"
#include "TTTBoard.h"
#include <assert.h>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include "Player.h"
#include "Bitmap.h"

CTTTBoardRender::CTTTBoardRender(CTTTBoard* board, CRenderer* renderer,/* size_t boxFaceSize,*/ size_t margin)
	: IRenderComponent("Background Renderer", renderer)
	, m_board(board)
/*	, m_boxFaceSize(boxFaceSize)*/
	, m_margin(margin)
{
	//assert(m_boxFaceSize > 99);
	assert(m_margin > 0);
}

CTTTBoardRender::~CTTTBoardRender(void)
{

}

void CTTTBoardRender::OnStart(void)
{

}

void CTTTBoardRender::OnRender(void)
{
	//size_t tlx = m_margin;
	//size_t tly = m_margin;

	const size_t displayWidth = al_get_display_width(al_get_current_display());
	const size_t displayHeight = al_get_display_height(al_get_current_display());
	const size_t gamePieceSize = m_board->GetGamePieceSize();
	const ALLEGRO_COLOR neutralPieceColor = al_map_rgb(0, 0, 255);
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			const size_t x1 = i * gamePieceSize;
			const size_t y1 = j * gamePieceSize;
			const size_t x2 = x1 + gamePieceSize;
			const size_t y2 = y1 + gamePieceSize;
			
			CPlayer* player = m_board->GetOwner(i, j);
			if (player)
				al_draw_scaled_bitmap(player->GetGamePiece()->GetData(), 0, 0, player->GetGamePiece()->GetWidth(), player->GetGamePiece()->GetHeight(), x1, y1, gamePieceSize, gamePieceSize, 0);
			else
				al_draw_filled_rectangle(i * m_board->GetGamePieceSize(), j * m_board->GetGamePieceSize(), x2, y2, neutralPieceColor);

			al_draw_rectangle(i * m_board->GetGamePieceSize(), j * m_board->GetGamePieceSize(), x2, y2, al_map_rgb(255, 255, 255), 2);
		}
	}
}

void CTTTBoardRender::OnFixedUpdate(void)
{

}

void CTTTBoardRender::OnUpdate(double dt)
{

}
