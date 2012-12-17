#ifndef CHECKERSPIECE_H
#define CHECKERSPIECE_H

#include "GamePiece.h"

class CCheckersBoard;
class CCheckersPiece: public IGamePiece
{
public:
	/// @param board The board this piece will be moving on.
	/// @param owner The player that owns this piece.
	CCheckersPiece(CCheckersBoard* board, CPlayer* owner);
	~CCheckersPiece(void);

	bool IsKinged(void) const { return m_isKinged; }

protected:
	bool Move(size_t col, size_t row);

private:
	CCheckersBoard* m_board;
	bool m_isKinged;
};

#endif