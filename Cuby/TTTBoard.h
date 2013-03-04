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

	CPlayer* GetOwner(size_t row, size_t col);
	bool IsMatchBeingPlayed(void) const { return m_matchBeingPlayed; }
	size_t GetGamePieceSize(void) const { return m_gamePieceSize; }

	bool Move(size_t row, size_t col, CPlayer* player);
	void Start(void);

protected:
	bool CheckForWin(size_t row, size_t col);
	/// Check if a spot is a winning spot for the owner of the spot horizontally.
	bool CheckForWinH(size_t row, size_t col);
	/// Check if a spot is a winning spot for the owner of the spot vertically.
	bool CheckForWinV(size_t row, size_t col);
	/// Check if a spot is a winning move for player diagonally(Top Right <-> Bottom Left)
	bool CheckForWinD1(size_t row, size_t col);
	/// Check if a spot is a winning move for player diagonally(Top Left <-> Bottom Right)
	bool CheckForWinD2(size_t row, size_t col);
	bool CheckForDraw(void) const;



	void Update(double dt);
	bool OnMatchStarted(void);
	bool OnMatchEnded(void);
	void ClearBoard(void);
private:
	std::array<CBitmap*, 2> m_pieces;
	std::array<std::array<CPlayer*, 3>, 3> m_board;
	CTTTBoardRender* m_boardRender;
	CPlayer* m_player1;
	CPlayer* m_player2;
	bool m_paused; /// Set to true when a match is ended.
	bool m_matchBeingPlayed;
	CPlayer* m_winner; /// Set to non-null when someone wins the game.
	CPlayer* m_curPlayer;
	size_t m_gamePieceSize; /// The width and height of each piece on the board.
};

#endif