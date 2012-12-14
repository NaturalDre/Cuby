#ifndef RENDERER_H
#define RENDERER_H

#include <list>

class IRenderComponent;
class CEngine;
class CRenderer
{
public:
	CRenderer(CEngine* engine);
	~CRenderer(void);

	void AddComponent(IRenderComponent* component);
	void RemoveComponent(IRenderComponent* component);
	void Render(void);
private:
	CEngine* m_engine;
	std::list<IRenderComponent*> m_renderList;
};
#endif