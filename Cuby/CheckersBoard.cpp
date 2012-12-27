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
		m_board[row][col] = GetOwner(GetSelected());
		m_board[GetSelected().row][GetSelected().col] = BLANK;
		m_selected.valid = false;
		if (m_curPlayer == ALPHA)
			m_curPlayer = BETA;
		else
			m_curPlayer = ALPHA;
	}
	return false;
}

bool CCheckersBoard::Select(size_t row, size_t col)
{
	const size_t OWNER = GetOwner(row, col);
	// It has to be the player's turn and the spot must
	// not be blank in order to select it.
	if (m_curPlayer != OWNER || OWNER == BLANK)
		return false;

	m_selected = RowCol(row, col, true);
	NOTE("Selected a piece.");
	return true;
}

size_t CCheckersBoard::GetOwner(size_t row, size_t col) const
{
	// Make sure the location is in bounds.
	if (row >= m_board.size() || col >= m_board[row].size())
		return BLANK;
	else
		return m_board[row][col];
}

size_t CCheckersBoard::GetPlayerOwner(const RowCol& rc)
{
	if (GetOwner(rc) == ALPHA || GetOwner(rc) == KING_ALPHA) 
		return ALPHA;
	else if (GetOwner(rc) == BETA || GetOwner(rc) == KING_BETA)
		return BETA;
	return BLANK;
}

bool CCheckersBoard::IsKing(const RowCol& rc)
{
	const size_t TYPE = GetOwner(rc);
	if (TYPE == KING_ALPHA || TYPE == KING_BETA)
		return true;
	return false;
}

bool CCheckersBoard::IsValid(const RowCol& rc)
{
	// warning: signed/unsigned mismatch
	if (rc.row < GetBoard().size() || rc.col < GetBoard()[rc.col].size())
		return true;
	return false;
}

bool CCheckersBoard::IsValidMove(const RowCol& src, const RowCol& drc)
{
	// Return false if src and drc are not valid positions, 
	// src is blank
	// or src and drc are owned by the same player.
	if (!IsValid(src) || !IsValid(drc) || GetPlayerOwner(src) == BLANK /*|| GetPlayerOwner(drc) == BLANK*/ || GetPlayerOwner(src) == GetPlayerOwner(drc))
		return false;

	const bool srcIsKing = IsKing(src);

	if (srcIsKing)
	{
		if (std::abs((src.row - drc.row)) == 1 && std::abs(src.row - drc.col) == 1)
			return true;
	}
	else
	{
		int owner = GetPlayerOwner(src);
		int a = ALPHA;
		if (GetPlayerOwner(src) == ALPHA)
		{
			if (src.row - drc.row == -1 && std::abs(src.col - drc.col) == 1)
				return true;
		}
		else
		{
			if (src.row - drc.row == 1 && std::abs(src.col - drc.col) == 1)
				return true;
		}
	}

	return false;
}