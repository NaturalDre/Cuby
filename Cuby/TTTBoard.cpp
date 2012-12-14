#include "TTTBoard.h"
#include "TTTBoardRender.h"
#include <iostream>
#include "Debug.h"
#include "Player.h"
#include "PlayerKeyboardInput.h"
#include "PlayerMouseInput.h"
#include "Engine.h"

CTTTBoard::CTTTBoard(CEngine* engine, size_t gamePieceSize)
	: IGameBoard(engine)
	, m_boardRender(nullptr)
	, m_board()
	, m_player1(nullptr)
	, m_player2(nullptr)
	, m_winner(nullptr)
	, m_paused(false)
	, m_matchBeingPlayed(false)
	, m_curPlayer(nullptr)
	, m_gamePieceSize(gamePieceSize)
{
	SetRenderer(GetEngine()->GetRenderer());
}

CTTTBoard::~CTTTBoard(void)
{

}

void CTTTBoard::Start(void)
{
	IGameObject::Start();
	{
		m_player1 = new CPlayer("Player1", GetEngine());
		auto keyboardInput = new CPlayerKeyboardInput(m_player1, this);
		m_player1->AddComponent(keyboardInput);
		m_player1->SetGamePiece("player1piece.png");
		GetEngine()->AddInputComponent(keyboardInput);
	}
	{
		m_player2 = new CPlayer("Player2", GetEngine());
		auto mouseInput = new CPlayerMouseInput(m_player2, this);
		m_player2->AddComponent(mouseInput);
		m_player2->SetGamePiece("player2piece.png");
		GetEngine()->AddInputComponent(mouseInput);
	}
}

void CTTTBoard::Update(double dt)
{
	IGameObject::Update(dt);
	if (m_winner && !m_paused)
	{
		m_paused = true;
		NOTE("We have a winner!");
		EndCurrentMatch();
	}
	else if (!m_paused && CheckForDraw())
	{
		m_paused = true;
		NOTE("We have a draw!");
		EndCurrentMatch();
	}
	//bool p1Win = CheckForWin(
}
bool CTTTBoard::CheckForWin(size_t col, size_t row)
{
	bool result(false);
	if (CheckForWinH(col, row) || CheckForWinV(col,row) || CheckForWinD1(col, row) || CheckForWinD2(col, row))
		return true;
	return false;
}

CPlayer* CTTTBoard::GetOwner(size_t x, size_t y)
{
	// Make sure the position is in bounds
	if (x < m_board.size() && y < m_board[x].size())
		return m_board[x][y];
	return nullptr;
}

bool CTTTBoard::Move(size_t x, size_t y, CPlayer* player)
{
	// Make sure it's the players turn and that the player isn't trying to
	// overwrite the other player's turn and that it doesn't already own 
	// the spot before we perform the move.
	if (player != m_curPlayer || GetOwner(x,y) != nullptr || GetOwner(x,y) == player)
		return false;
	// Make sure the position is in bounds
	if ((x >= 0 && x < 3) && (y >= 0 && y < 3))
	{
		m_board[x][y] = player;
		if (CheckForWin(x, y))
			m_winner = player;
		// TODO: Make neater
		if (player == m_player1)
			m_curPlayer = m_player2;
		else
			m_curPlayer = m_player1;
		// We successfully completed the move.
		return true;
	}
	// We failed to complete the move.
	return false;
}
/// Left <-> Right
bool CTTTBoard::CheckForWinH(size_t col, size_t row)
{
	const CPlayer* owner = GetOwner(col, row);
	// Seeing as we know 'owner' has the spot (col,row), we
	// don't need to check it and can just initialize
	// count to 1.
	size_t count(1);
	// Check from right to left for a win.
	{
		if (GetOwner(col - 1, row) == owner)
			++count;
		if (GetOwner(col - 2, row) == owner)
			++count;
	}
	// Check from left to right for a win.
	{
		if (GetOwner(col + 1, row) == owner)
			++count;
		if (GetOwner(col + 2, row) == owner)
			++count;
	}
	// If we found 3 spots, we have a winner.
	if (count == 3)
		return true;

	return false;
}

/// Top <-> Bottom
bool CTTTBoard::CheckForWinV(size_t col, size_t row)
{
	const CPlayer* owner = GetOwner(col, row);
	// Seeing as we know 'owner' has the spot (col,row), we
	// don't need to check it and can just initialize
	// count to 1.
	size_t count(1);
	// Check bottom to top for a win.
	{
		if (GetOwner(col, row - 1) == owner)
			++count;
		if (GetOwner(col, row - 2) == owner)
			++count;
	}
	// Check top to bottom for a win.
	{
		if (GetOwner(col, row + 1) == owner)
			++count;
		if (GetOwner(col, row + 2) == owner)
			++count;
	}
	// If we found 3 spots, we have a winner.
	if (count == 3)
		return true;
	return false;
}

/// Top Right <-> Bottom Left
bool CTTTBoard::CheckForWinD1(size_t col, size_t row)
{
	const CPlayer* owner = GetOwner(col, row);
	// Seeing as we know 'owner' has the spot (x,y), we
	// don't need to check it and can just initialize
	// count to 1.
	size_t count(1);
	// Check Top Right -> Bottom Left for win.
	{
		if (GetOwner(col - 1, row + 1) == owner)
			++count;
		if (GetOwner(col - 2, row + 2) == owner)
			++count;
	}
	// Check Bottom Left -> Top Right for win.
	{
		if (GetOwner(col + 1, row - 1) == owner)
			++count;
		if (GetOwner(col + 2, row - 2) == owner)
			++count;
	}
	// If the count is 3, we have a winner.
	if (count == 3)
		return true;

	return false;
}

// Top Left <-> Bottom Right 
bool CTTTBoard::CheckForWinD2(size_t col, size_t row)
{
	const CPlayer* owner = GetOwner(col, row);
	// Seeing as we know 'owner' has the spot (x,y), we
	// don't need to check it and can just initialize
	// count to 1.
	size_t count(1);
	// Check Bottom Right -> Top Left for a win,
	{
		if (GetOwner(col - 1, row - 1) == owner)
			++count;
		if (GetOwner(col - 2, row - 2) == owner)
			++count;
	}
	// Check Top Left -> Bottom Right for a win.
	{
		if (GetOwner(col + 1, row + 1) == owner)
			++count;
		if (GetOwner(col + 2, row + 2) == owner)
			++count;
	}
	// If the count is 3, we have a winner.
		if (count == 3)
			return true;
	return false;
}

bool CTTTBoard::CheckForDraw(void) const
{
	size_t count(0);
	for (size_t i(0); i < m_board.size(); ++i)
		for (size_t j(0); j < m_board[i].size(); ++j)
			if (m_board[i][j] == nullptr)
				return false;
	return true;
}

void CTTTBoard::OnMatchStarted(void)
{
	NOTE("Attempting to start a new match...");
	// We don't want to start a new match if one is already being played,
	// p1/p2 are nullpointers, or if p1/p2 are the same player.
	if (IsMatchBeingPlayed() || !m_player1 || !m_player2 || m_player1 == m_player2)
		return;
	ClearBoard();
	m_winner = nullptr;
	m_paused = false;
	m_matchBeingPlayed = true;
	m_curPlayer = m_player1;

	NOTE("Match started. Player1 (Keyboard with numpad), goes first. Player2(Mouse clicks), goes second.");
}

void CTTTBoard::OnMatchEnded(void)
{
	//m_player1 = nullptr;
	//m_player2 = nullptr;
	m_curPlayer = nullptr;
	m_matchBeingPlayed = false;
	NOTE("Match ended.");
}

void CTTTBoard::ClearBoard(void)
{
	for (size_t i(0); i < m_board.size(); ++i)
		for (size_t j(0); j < m_board[i].size(); ++j)
			m_board[i][j] = nullptr;
}