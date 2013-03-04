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
	inline size_t GetPieceAt(size_t row, size_t col) const 
	{ 
		if (!IsValidPosition(row, col)) 
			return BLANK; 
		else 
			return m_board[row][col]; 
	}
	/// Returns what piece occupies a position.
	/// @param rc The position you want to check.
	/// \return The piece that occupies the position. (BLANK, ALPHA, BETA, KING_ALPHA, KING_BETA)
	inline size_t GetPieceAt(const RowCol& rc) const { return GetPieceAt(rc.row, rc.col); }
	/// Returns what *PLAYER* owns the piece that occupies this spot.
	/// @param rc The position you want to check.
	/// \return Either ALPHA, BETA, or BLANK. Remember, ALPHA is Player1, BETA is Player2.
	size_t GetPlayerAt(const RowCol& rc);
	inline RowCol GetSelected(void) const { return m_selected; }
	/// Checks if the piece at a location is a king.
	bool IsKing(const RowCol& rc);
	/// Returns whether or not the position exists on the gameboard.
	bool IsValidPosition(size_t row, size_t col) const 
	{ 
		if ((row < GetBoard().size() && row >= 0) && (col < GetBoard().size() && col >= 0)) 
			return true; 
		return false; 
	}
	bool IsValidPosition(const RowCol& rc) const { return IsValidPosition(rc.row, rc.col); }
	// Returns whether or not drc is 2 spaces diagnally from src.
	bool IsJumpMove(const RowCol& src, const RowCol& drc) 
	{ 
		if (std::abs(src.row - drc.row) == 2 && std::abs(drc.col - drc.col) == 2)
			return true;
		return false;
	}
	// Returns whether or not drc is 1 space diagnal from src.
	bool IsNormalMove(const RowCol& src, const RowCol& drc)
	{
		if (std::abs(src.row - drc.row) == 1 && std::abs(drc.col - drc.col) == 1)
			return true;
		return false;
	}
	bool CanMove(const RowCol& src, const RowCol& drc);
	bool CanJump(const RowCol& src, const RowCol& drc);
	const std::array<std::array<size_t, 8>, 8>& GetBoard(void) const { return m_board; }

	size_t GetXMargin(void) const { return m_xMargin; }
	size_t GetYMargin(void) const { return m_yMargin; }
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
	/// \note This should only be called by OnMatchStarted()
	void PlacePieces(void);

	/// Helper function to handle a regular move.
	/// \note Called only by Move().
	void HandleMove(const RowCol& drc);
	/// Helper function to handle a jump move.
	/// \note Called only by Move().
	void HandleJump(const RowCol& drc);
	/// Helper function to handle a successful move.
	/// \note Called only by Move().
	void HandleSuccessfulMove(const RowCol& drc);

	bool CanAlphaMove(void);
	bool CanBetaMove(void);


private:
	std::array<std::array<size_t, 8>, 8> m_board;
	size_t m_curPlayer;
	RowCol m_selected;
	size_t m_removedAlphaPieces;
	size_t m_removedBetaPieces;
	const size_t m_xMargin;
	const size_t m_yMargin;
};

#endif