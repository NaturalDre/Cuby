#include "CheckersPiece.h"
#include <assert.h>
CCheckersPiece::CCheckersPiece(CCheckersBoard* board, CPlayer* owner)
	: IGamePiece(owner)
	, m_board(board)
	, m_isKinged(false)
{

}

CCheckersPiece::~CCheckersPiece(void)
{

}

bool CCheckersPiece::Move(size_t col, size_t row)
{
	if (!m_board || !GetOwner())
		return false;



	return false;
}