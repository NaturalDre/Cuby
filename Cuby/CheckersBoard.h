#ifndef CHECKERSBOARD_H
#define CHEC

#include "GameBoard.h"
#include <array>

class CCheckersPiece;
class CCheckersBoard: public IGameBoard
{
public:
	static const size_t BLANK = 0;
	static const size_t ALPHA = 1;
	static const size_t BETA = 2;
	static const size_t KING_ALPHA = 3;
	static const size_t KING_BETA = 4;
	
	CCheckersBoard(CEngine* engine);
	~CCheckersBoard(void);

	bool Move(size_t row, size_t col);

protected:
	void Start(void);
	void Update(double dt);

	bool OnMatchStarted(void);
	bool OnMatchEnded(void);

	/// Removes every gamepiece on the board.
	void ClearBoard(void);
	/// Add each gamepiece for both players to the board.
	/// @note This should only be called by St
	void PlacePieces(void);
private:
	std::array<std::array<size_t, 8>, 8> m_board;
};

#endif