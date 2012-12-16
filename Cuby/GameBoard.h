#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include <map>

class CRenderer;
class IGamePiece;
/// @note Classes derived from this need to implement
///		  IGameObject's pure virtuals.
class IGameBoard: public IGameObject
{
protected:
	void SetRenderer(CRenderer* renderer) { m_renderer = renderer; }
public:
	IGameBoard(CEngine* engine): IGameObject("GameBoard", engine) { }
	virtual ~IGameBoard(void) { }

	//void Start(void) { IGameObject::Start(); }
	//void Update(double dt) { IGameObject::Update(dt); }
	//void FixedUpdate(void) { IGameObject::FixedUpdate(); }

	inline CRenderer* GetRenderer(void) const { return m_renderer; }
	inline size_t GetX(void) const { return m_x; }
	inline void SetX(size_t x) { m_x = x; }
	inline size_t GetY(void) const { return m_y; }
	inline void SetY(size_t y) { m_y = y; }
	//inline void SetGamePieceSize(const std::string& name, IGamePiece* gamePiece) { if (!name.empty()) m_gamePieces[name] = gamePiece; }
	//inline IGamePiece* GetGamePiece(const std::string& name) const { if (m_gamePieces.find( }
private:
	std::map<const std::string, IGamePiece*> m_gamePieces;
	CRenderer* m_renderer;
	size_t m_x; /// Top left x-position of the board.
	size_t m_y; /// Top right y-position of the board.};
};
#endif