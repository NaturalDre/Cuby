#ifndef TTTSCENE_H
#define TTTSCENE_H

#include "GameBoard.h"
#include <array>

class CBitmap;
class CPlayer;
class CTTTBoardRender;
class CTTTBoard: public IGameBoard
{
public:
	CTTTBoard(CEngine* engine, size_t gamePieceSize = 200);
	~CTTTBoard(void);

	void Render(void);
	void SetPlayer1(CPlayer* player1) { if (m_player2 != player1) m_player1 = player1; }
	void SetPlayer2(CPlayer* player2) { if (m_player1 != player2) m_player2 = player2; }
	CPlayer* GetPlayer1(void) const { return m_player1; }
	CPlayer* GetPlayer2(void) const { return m_player2; }

	CPlayer* GetOwner(size_t x, size_t y);
	bool IsMatchBeingPlayed(void) const { return m_matchBeingPlayed; }
	size_t GetGamePieceSize(void) const { return m_gamePieceSize; }

	bool Move(size_t x, size_t y, CPlayer* player);
	void StartNewMatch(void) { OnMatchStarted(); }
	void EndCurrentMatch(void) { OnMatchEnded(); }

protected:
	bool CheckForWin(size_t x, size_t y);
	/// Check if a spot is a winning spot for the owner of the spot horizontally.
	bool CheckForWinH(size_t col, size_t row);
	/// Check if a spot is a winning spot for the owner of the spot vertically.
	bool CheckForWinV(size_t col, size_t row);
	/// Check if a spot is a winning move for player diagonally(Top Right <-> Bottom Left)
	bool CheckForWinD1(size_t col, size_t row);
	/// Check if a spot is a winning move for player diagonally(Top Left <-> Bottom Right)
	bool CheckForWinD2(size_t col, size_t row);
	bool CheckForDraw(void) const;


	void Start(void);
	void Update(double dt);
	void OnMatchStarted(void);
	void OnMatchEnded(void);
	void ClearBoard(void);
private:
	std::array<CBitmap*, 2> m_pieces;
	std::array<std::array<CPlayer*, 3>, 3> m_board;
	CTTTBoardRender* m_boardRender;
	CPlayer* m_player1;
	CPlayer* m_player2;
	bool m_paused;
	bool m_matchBeingPlayed;
	CPlayer* m_winner;
	CPlayer* m_curPlayer;
	/// The width and height of each piece on the board.
	size_t m_gamePieceSize;
};

#endif