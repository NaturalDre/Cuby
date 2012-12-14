#ifndef SCENE_H
#define SCENE_H

class CRenderer;
#include "GameObject.h"

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

	CRenderer* GetRenderer(void) const { return m_renderer; }

private:
	CRenderer* m_renderer;
};
#endif