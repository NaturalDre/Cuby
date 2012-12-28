#include "CheckersBoard.h"
#include "Debug.h"
#include <list>

// In Checkers, each player starts with pieces on the black squares of the first 3 rows on their side.
const size_t ROWS_PER_PLAYER = 3;


CCheckersBoard::CCheckersBoard(CEngine* engine)
	: IGameBoard(engine)
	, m_board()
	, m_curPlayer(0)
	, m_selected(0,0, false)
	, m_removedAlphaPieces(0)
	, m_removedBetaPieces(0)
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
}

bool CCheckersBoard::OnMatchStarted(void)
{
	NOTE("Attemping to start match...");
	ClearBoard();
	PlacePieces();

	// Alpha always goes first.
	m_curPlayer = ALPHA;
	return false;
}

bool CCheckersBoard::OnMatchEnded(void)
{
	return false;
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

	if (IsValidMove(GetSelected(), RowCol(row,col, true)))
	{
		if (GetPlayerAt(RowCol(row,col)) == ALPHA)
			++m_removedAlphaPieces;
		else if(GetPlayerAt(RowCol(row,col)) == BETA)
			++m_removedBetaPieces;
		m_board[row][col] = GetPieceAt(GetSelected());
		m_board[GetSelected().row][GetSelected().col] = BLANK;
		m_selected.valid = false;

		if (m_curPlayer == ALPHA && row == 7)
		{
			m_board[row][col] = KING_ALPHA;
			NOTE("Alpha piece has been crowned.");
		}
		else if (m_curPlayer == BETA && row == 0)
		{
			m_board[row][col] = KING_BETA; 
			NOTE("Beta piece has been crowned.");
		}

		NOTE("Piece successfully moved.");
		if (m_removedAlphaPieces == 12 || m_removedBetaPieces == 12)
		{
			NOTE("We have a winner(Checkers)");
		}
		if (m_curPlayer == ALPHA)
			m_curPlayer = BETA;
		else
			m_curPlayer = ALPHA;
	}
	return false;
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

// This function is not finished. Pieces need to jump OVER an enemy piece,
// not ONTO its spot.
bool CCheckersBoard::IsValidMove(const RowCol& src, const RowCol& drc)
{
	// Return false if src and drc are not valid positions, 
	// src is blank
	// or src and drc are owned by the same player.
	if (!IsValidPosition(src) || !IsValidPosition(drc) || GetPlayerAt(src) == BLANK /*|| GetPlayerOwner(drc) == BLANK*/ || GetPlayerAt(src) == GetPlayerAt(drc))
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