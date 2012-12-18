#include "CheckersBoard.h"

// In Checkers, each player starts with pieces on the black squares of the first 3 rows on their side.
static const size_t ROWS_PER_PLAYER = 3;

CCheckersBoard::CCheckersBoard(CEngine* engine)
	: IGameBoard(engine)
	, m_board()
{

}

CCheckersBoard::~CCheckersBoard(void)
{

}

void CCheckersBoard::Start(void)
{

}

void CCheckersBoard::Update(double dt)
{

}

bool CCheckersBoard::OnMatchStarted(void)
{
	ClearBoard();
	PlacePieces();
	return false;
}

bool CCheckersBoard::OnMatchEnded(void)
{
	return false;
}

void CCheckersBoard::ClearBoard(void)
{
	m_board.fill(std::array<size_t, 8>());
}

// TODO: Improve this function.
void CCheckersBoard::PlacePieces(void)
{
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
}