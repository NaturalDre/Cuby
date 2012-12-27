#ifndef CHECKERSBOARDRENDER_H
#define CHECKERSBOARDRENDER_H

#include "RenderComponent.h"
#include "Bitmap.h"

class CCheckersBoard;
class CCheckersBoardRender: public IRenderComponent
{
public:
	CCheckersBoardRender(CCheckersBoard* board, CRenderer* renderer);
	~CCheckersBoardRender(void);

protected:
	void OnRender(void);
	/// Called when the scene is started.
	void OnStart(void);
	/// Called when the scene is updated.
	void OnUpdate(double dt) { }
	/// Called every fixed timestep.
	void OnFixedUpdate(void) { }
private:
	CCheckersBoard* m_board;
	CBitmap* m_alphaPiece;
	CBitmap* m_alphaKingPiece;
	CBitmap* m_betaPiece;
	CBitmap* m_betaKingPiece;
};

#endif