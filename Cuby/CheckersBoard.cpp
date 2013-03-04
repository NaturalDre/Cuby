#include "CheckersBoard.h"
#include "Debug.h"
#include <list>

// In Checkers, each player starts with pieces on the black squares of the first 3 rows on their side.
const size_t ROWS_PER_PLAYER = 3;


CCheckersBoard::CCheckersBoard(CEngine* engine)
	: IGameBoard(engine, "Checkers")
	, m_board()
	, m_curPlayer(0)
	, m_selected(0,0, false)
	, m_removedAlphaPieces(0)
	, m_removedBetaPieces(0)
	, m_xMargin(0)
	, m_yMargin(100)
{
	SetPieceWidth(64);
	SetPieceHeight(64);
}

CCheckersBoard::~CCheckersBoard(void)
{

}

void CCheckersBoard::Start(void)
{
	IGameObject::Start();
}

void CCheckersBoard::Update(double dt)
{
	IGameObject::Update(dt);

	if (GetCurPlayer() != BLANK && (!CanAlphaMove() || !CanBetaMove()))
		NOTE("A side is unable to make a move.");
}

bool CCheckersBoard::OnMatchStarted(void)
{
	NOTE("Attemping to start match...");
	ClearBoard();
	PlacePieces();
	// Alpha always goes first.
	m_curPlayer = ALPHA;
	return true;
}

bool CCheckersBoard::OnMatchEnded(void)
{
	NOTE("Attempting to end a Tic Tac Toe match...");
	m_removedAlphaPieces = 0;
	m_removedBetaPieces = 0;
	m_selected.valid = false;
	m_curPlayer = BLANK;
	ClearBoard();
	return true;
}

void CCheckersBoard::ClearBoard(void)
{
	NOTE("Clearing board...");
	m_board.fill(std::array<size_t, 8>());
	NOTE("Board cleared.");
}

// TODO: Improve this function.
void CCheckersBoard::PlacePieces(void)
{
	NOTE("Placing pieces...");
	// Note: I assume 0 to be even.
	bool isOdd = false;
	// First top 3 rows
	for (size_t row = 0; row < ROWS_PER_PLAYER; ++row)
	{
		size_t col(1);
		if (isOdd)
			col = 0;
		for (; col < m_board[row].size(); col += 2)
			m_board[row][col] = ALPHA;
		isOdd = !isOdd;
	}
	// Fill bottom 3 rows
	isOdd = true;
	for (size_t row = m_board.size() - ROWS_PER_PLAYER; row < m_board.size(); ++row)
	{
		size_t col(1);
		if (isOdd)
			col = 0;
		for (; col < m_board[row].size(); col += 2)
			m_board[row][col] = BETA;
		isOdd = !isOdd;
	}

	NOTE("Pieces have been placed.");
}

bool CCheckersBoard::Move(size_t row, size_t col)
{
	if (!GetSelected().valid)
		return false;

	const RowCol drc(row, col);

	// Have we completed a move successfully?
	bool moveSuccessful(false);
	// Is the move being attemped a valid move? (Are they trying to move 1 unit diagnally?
	if (CanMove(GetSelected(), RowCol(row,col)))
	{
		HandleMove(drc);
		moveSuccessful = true;
	}
	// Is the move being attemped a valid jump? (Are they trying to move 2 units diagnally over an enemy unit?
	else if (CanJump(GetSelected(), RowCol(row,col)))
	{
		HandleJump(drc);
		moveSuccessful = true;
	}
	// If a move is successful we need to check/set a few things.
	if (moveSuccessful)
		HandleSuccessfulMove(drc);
	return false;
}

void CCheckersBoard::HandleMove(const RowCol& drc)
{
	m_board[drc.row][drc.col] = GetPieceAt(GetSelected());
	m_board[GetSelected().row][GetSelected().col] = BLANK;
}

void CCheckersBoard::HandleJump(const RowCol& drc)
{
	int rowModifier(-1);
	int colModifier(-1);
	if (GetSelected().row - drc.row < 0)
		rowModifier = 1;
	if (GetSelected().col - drc.col < 0)
		colModifier = 1;
	m_board[drc.row][drc.col] = GetPieceAt(GetSelected());
	m_board[GetSelected().row][GetSelected().col] = BLANK;
	m_board[GetSelected().row + rowModifier][GetSelected().col + colModifier] = BLANK;

	if (GetPlayerAt(RowCol(drc.row,drc.col)) == ALPHA)
		++m_removedAlphaPieces;
	else if(GetPlayerAt(RowCol(drc.row,drc.col)) == BETA)
		++m_removedBetaPieces;
}

void CCheckersBoard::HandleSuccessfulMove(const RowCol& drc)
{
	// If Alpha got a piece to the end, crown it.
	if (m_curPlayer == ALPHA && drc.row == 7 && GetPieceAt(drc.row, drc.col) != KING_ALPHA)
	{
		m_board[drc.row][drc.col] = KING_ALPHA;
		NOTE("Alpha piece has been crowned.");
	}
	// If Beta got a piece ot the end, crown it.
	else if (m_curPlayer == BETA && drc.row == 0 && GetPieceAt(drc.row, drc.col) != KING_BETA)
	{
		m_board[drc.row][drc.col] = KING_BETA; 
		NOTE("Beta piece has been crowned.");
	}

	// This player is about to be switched so the selected piece needs to be invalidated.
	// TODO: Make sure to check if it's still possible to jump over another piece before 
	//		 ending the current player's turn(Unless the piece they moved was crowned, then
	//		 it doesn't matter if it can capture another piece.)
	m_selected.valid = false;
	// Switch players.
	if (m_curPlayer == ALPHA)
		m_curPlayer = BETA;
	else
		m_curPlayer = ALPHA;

	NOTE("Piece successfully moved.");
	if (m_removedAlphaPieces == 12 || m_removedBetaPieces == 12)
	{
		NOTE("We have a winner(Checkers)");
	}
}

bool CCheckersBoard::Select(size_t row, size_t col)
{
	const size_t OWNER = GetPlayerAt(RowCol(row, col));
	// It has to be the player's turn and the spot must
	// not be blank in order to select it.
	if (m_curPlayer != OWNER || OWNER == BLANK)
		return false;

	m_selected = RowCol(row, col, true);
	NOTE("Selected a piece.");
	return true;
}

size_t CCheckersBoard::GetPlayerAt(const RowCol& rc)
{
	if (GetPieceAt(rc) == ALPHA || GetPieceAt(rc) == KING_ALPHA) 
		return ALPHA;
	else if (GetPieceAt(rc) == BETA || GetPieceAt(rc) == KING_BETA)
		return BETA;
	return BLANK;
}

bool CCheckersBoard::IsKing(const RowCol& rc)
{
	const size_t TYPE = GetPieceAt(rc);
	if (TYPE == KING_ALPHA || TYPE == KING_BETA)
		return true;
	return false;
}

bool CCheckersBoard::CanMove(const RowCol& src, const RowCol& drc)
{
	// Return false if src and drc are not valid positions, 
	// src is blank
	// or src and drc are owned by the same player.
	if (!IsValidPosition(src) || !IsValidPosition(drc) || GetPlayerAt(src) == BLANK || GetPlayerAt(src) == GetPlayerAt(drc))
		return false;
	// To do a move, the destination location must be one diagnal unit away and 
	// the destination location must be blank.
	if (GetPlayerAt(drc) != BLANK || std::abs(src.row - drc.row) != 1 || std::abs(src.col - drc.col) != 1)
		return false;
	// Kings can move forward and backwards.
	if (IsKing(src))
	{
		// A king MUST be moved by one column and one row.
		if (std::abs((src.row - drc.row)) == 1 && std::abs(src.col - drc.col) == 1)
			return true;
	}
	else
	{
		// Regular Alpha pieces can only move down.
		if (GetPlayerAt(src) == ALPHA)
		{
		// Player alpha can only move a regular piece DOWN one row and one column(direction doesn't matter)
			if (src.row - drc.row == -1 && std::abs(src.col - drc.col) == 1)
				return true;
		}
		// Regular Beta pieces can only move up.
		else if (GetPlayerAt(src) == BETA)	// This is kind of pointless right now since
		{										// BETA can be the only other answer. But I want to be safe for the future.
			if (src.row - drc.row == 1 && std::abs(src.col - drc.col) == 1)
				return true;
		}
	}

	return false;
}

bool CCheckersBoard::CanJump(const RowCol& src, const RowCol& drc)
{
	// Return false if src and drc are not valid positions, 
	// src is blank
	// or src and drc are owned by the same player.
	if (!IsValidPosition(src) || !IsValidPosition(drc) || GetPlayerAt(src) == BLANK || GetPlayerAt(src) == GetPlayerAt(drc))
		return false;

	// To do a jump, the destination location must be two diagnal units away and 
	// the destination location must be blank.
	if (GetPlayerAt(drc) != BLANK || std::abs(src.row - drc.row) != 2 || std::abs(src.col - drc.col) != 2)
		return false;

	// The difference between the source position and destination position.
	const RowCol diff(src.row - drc.row, src.col - drc.col);
	// Constants for positions one diagnal unit away from src
	const RowCol BR(src.row + 1, src.col + 1); // Bottom-right
	const RowCol BL(src.row + 1, src.col - 1); // Bottom-left
	const RowCol TR(src.row - 1, src.col + 1); // Top-right
	const RowCol TL(src.row - 1, src.col - 1); // Top-left

	// Kings can move forward and backwards.
	// A king MUST be moved by one column and one row.
	if (IsKing(src))
	{
		RowCol pos(0,0, false);
		if (diff.row < 0 && diff.col > 0) 
			pos = BL;	// They are jumping at the bottom-left square.
		else if(diff.row < 0 && diff.col < 0)
			pos = BR;	// They are jumping at the bottom-right square.
		else if(diff.row > 0 && diff.col > 0)
			pos = TL;	// They are jumping at the top-left square.
		else if (diff.row > 0 && diff.col < 0)
			pos = TR;	// They are jumping at the top-right square.

		if (GetPlayerAt(src) == ALPHA)
		{

			if (std::abs(diff.row) == 2 && std::abs(diff.col) == 2)
			{
				// Make sure we're jumping OVER an enemy piece.
				if (pos.valid && GetPlayerAt(pos) == BETA)
					return true;
				return false;
			}
		}
		else if (GetPlayerAt(src) == BETA)
		{
			if (std::abs(diff.row) == 2 && std::abs(diff.col) == 2)
			{
				// Make sure we're jumping OVER an enemy piece.
				if (pos.valid && GetPlayerAt(pos) == ALPHA)
					return true;
				return false;
			}
		}
	}
	else
	{
		// Regular Alpha pieces can only move down.
		if (GetPlayerAt(src) == ALPHA)
		{
		// Player alpha can only move a regular piece DOWN one row and one column(direction doesn't matter)
			if (diff.row == -2 && std::abs(diff.col))
			{
				// Make sure we're jumping OVER an enemy piece.
				const RowCol p1rc(src.row + 1, src.col + 1);
				const RowCol p2rc(src.row + 1, src.col -1);
				if (GetPlayerAt(p1rc) == BETA || GetPlayerAt(p2rc) == BETA)
					return true;
			}
		}
		// Regular Beta pieces can only move up.
		else if (GetPlayerAt(src) == BETA)	// This is kind of pointless right now since
		{										// BETA can be the only other answer. But I want to be safe for the future.
			if (diff.row == 2 && std::abs(diff.col) == 2)
			{
				// Make sure we're jumping OVER an enemy piece.
				const RowCol p1rc(src.row - 1, src.col + 1);
				const RowCol p2rc(src.row - 1, src.col -1);
				if (GetPlayerAt(p1rc) == ALPHA || GetPlayerAt(p2rc) == ALPHA)
					return true;
			}
		}
	}
	return false;
}

bool CCheckersBoard::CanAlphaMove(void)
{
	for (size_t row = 0; row < m_board.size(); ++row)
	{
		for (size_t col = 0; col < m_board[row].size(); ++col)
		{
			const RowCol src(row, col);
			if (GetPlayerAt(src) == ALPHA && (CanMove(src, RowCol(src.row + 1, src.col + 1)) ||
				CanMove(src, RowCol(src.row + 1, src.col - 1)) ||
				CanMove(src, RowCol(src.row - 1, src.col + 1)) ||
				CanMove(src, RowCol(src.row - 1, src.col - 1))))
				return true;
		}
	}
	return false;
}

bool CCheckersBoard::CanBetaMove(void)
{
	for (size_t row = 0; row < m_board.size(); ++row)
	{
		for (size_t col = 0; col < m_board[row].size(); ++col)
		{
			const RowCol src(row, col);
			if (GetPlayerAt(src) == BETA && (CanMove(src, RowCol(src.row - 1, src.col + 1)) ||
				CanMove(src, RowCol(src.row - 1, src.col - 1)) ||
				CanMove(src, RowCol(src.row + 1, src.col + 1)) ||
				CanMove(src, RowCol(src.row + 1, src.col - 1))))
				return true;
		}
	}	
	return false;
}