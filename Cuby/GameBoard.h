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

	inline void SetPieceWidth(size_t width) { if (width > 0) m_pieceWidth = width; }
	inline void SetPieceHeight(size_t height) { if (height > 0) m_pieceHeight = height; }
public:
	IGameBoard(CEngine* engine): IGameObject("GameBoard", engine), m_x(0), m_y(0), m_pieceWidth(32), m_pieceHeight(32) { }
	virtual ~IGameBoard(void) { }

	inline CRenderer* GetRenderer(void) const { return m_renderer; }
	/// \return The X-position of the top left of the board when rendered,
	inline size_t GetX(void) const { return m_x; }
	/// @param x X-position of the top left of the board when rendered.
	inline void SetX(size_t x) { m_x = x; }
	/// \return The Y-position of the top left of the board when rendered.
	inline size_t GetY(void) const { return m_y; }
	/// @param y Y-position of the top left of the board when rendered.
	inline void SetY(size_t y) { m_y = y; }


	inline size_t GetPieceWidth(void) const { return m_pieceWidth; }
	inline size_t GetPieceHeight(void) const { return m_pieceHeight; }

	virtual bool OnMatchStarted(void) = 0;
	virtual bool OnMatchEnded(void) = 0;

	virtual bool StartNewMatch(void) { return OnMatchStarted(); }
	virtual bool EndCurrentMatch(void) { return OnMatchEnded(); }

private:
	std::map<const std::string, IGamePiece*> m_gamePieces;
	CRenderer* m_renderer;
	size_t m_x; /// Top left x-position of the board.
	size_t m_y; /// Top right y-position of the board.
	size_t m_pieceWidth;
	size_t m_pieceHeight;
};
#endif