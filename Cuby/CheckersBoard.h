#ifndef CHECKERSBOARD_H
#define CHEC

#include "GameBoard.h"
#include <list>

class IGamePiece;
class CCheckersBoard: public IGameBoard
{
public:
	CCheckersBoard(CEngine* engine);
	~CCheckersBoard(void);

	bool Move(size_t row, size_t col);

protected:
	void Start(void);
	void Update(double dt);
private:
	std::list<IGamePiece*> m_gamePieces;
};

#endif