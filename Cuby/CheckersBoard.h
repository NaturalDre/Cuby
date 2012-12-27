#ifndef CHECKERSBOARD_H
#define CHEC

#include "GameBoard.h"
#include <array>


struct RowCol
{
	int row;
	int col;
	bool valid;
	RowCol(size_t r = 0, size_t c = 0, bool v = true) : row(r), col(c), valid(v) { }
};

class CCheckersPiece;
class CCheckersBoard: public IGameBoard
{
public:
	static const size_t BLANK = 0;
	/// Note: I refer to Player1 as ALPHA
	static const size_t ALPHA = 1;
	/// Note: I refer to Player2 as BETA
	static const size_t BETA = 2;
	static const size_t KING_ALPHA = 3;
	static const size_t KING_BETA = 4;
	
	CCheckersBoard(CEngine* engine);
	~CCheckersBoard(void);

	bool Move(size_t row, size_t col);
	bool Select(size_t row, size_t col);
	inline size_t GetCurPlayer(void) const { return m_curPlayer; }
	size_t GetOwner(size_t row, size_t col) const;
	/// Returns what piece occupies a position.
	/// @param rc The position you want to check.
	/// \return The piece that occupies the position. (BLANK, ALPHA, BETA, KING_ALPHA, KING_BETA)
	inline size_t GetOwner(const RowCol& rc) const { return GetOwner(rc.row, rc.col); }
	/// Returns what *PLAYER* owns the piece that occupies this spot.
	/// @param rc The position you want to check.
	/// \return Either ALPHA, BETA, or BLANK. Remember, ALPHA is Player1, BETA is Player2.
	size_t GetPlayerOwner(const RowCol& rc);
	inline RowCol GetSelected(void) const { return m_selected; }
	bool IsKing(const RowCol& rc);
	bool IsValid(const RowCol& rc);
	const std::array<std::array<size_t, 8>, 8>& GetBoard(void) const { return m_board; }
protected:
	void Start(void);
	void Update(double dt);

	/// Called when the user wants to start a new game.
	/// \return Whether or not it successfully started.
	bool OnMatchStarted(void);
	/// Called when the use wants to end the current game.
	/// \return Whether or not it successfully ended.
	bool OnMatchEnded(void);

	/// Removes every gamepiece on the board.
	void ClearBoard(void);
	/// Add each gamepiece for both players to the board.
	/// @note This should only be called by St
	void PlacePieces(void);

	/// Can this move be made?
	/// @param src The position of the selected piece.
	/// @param drc The position you want to move to.
	/// \return Whether or not the move is valid.
	bool IsValidMove(const RowCol& src, const RowCol& drc);
private:
	std::array<std::array<size_t, 8>, 8> m_board;
	size_t m_curPlayer;
	RowCol m_selected;
};

#endif