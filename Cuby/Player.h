#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class CBitmap;
class CPlayer: public IGameObject
{
public:
	CPlayer(const std::string& name, CEngine* engine);
	~CPlayer(void);

	void SetGamePiece(const std::string& filename);
	CBitmap* GetGamePiece(void) const { return m_gamePiece; }

	size_t GetWins(void) const { return m_wins; }
	size_t GetLosses(void) const { return m_losses; }
	size_t GetDraws(void) const { return m_draws; }

	void Start(void);

protected:


private:
	std::string m_gamePieceFilename;
	CBitmap* m_gamePiece;
	size_t m_wins;
	size_t m_losses;
	size_t m_draws;
};
#endif