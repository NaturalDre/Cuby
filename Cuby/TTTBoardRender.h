#ifndef TTTBOARDRENDER_H
#define TTTBOARDRENDER_H

#include "RenderComponent.h"

class CTTTBoard;
class CTTTBoardRender: public IRenderComponent
{
public:
	CTTTBoardRender(CTTTBoard* board, CRenderer* renderer,/* size_t boxFaceSize = 200,*/ size_t m_margin = 100);
	~CTTTBoardRender(void);

	//size_t GetBoxFaceSize(void) const { return m_boxFaceSize; }
protected:
	void OnStart(void);
	void OnFixedUpdate(void);
	void OnUpdate(double dt);
	void OnRender(void);

private:
	CTTTBoard* m_board;
	//size_t m_boxFaceSize;
	size_t m_margin;
};
#endif