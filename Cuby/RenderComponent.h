#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Component.h"

class CRenderer;
class IRenderComponent: public IComponent
{
public:
	IRenderComponent(const std::string& name, CRenderer* m_renderer);
	~IRenderComponent(void);
	/// Proxy for OnRender();
	void Render(void) { OnRender(); }
protected:
	///// Called at the beginning of a scene.
	//virtual void OnStart(void) = 0;
	///// Called once per frame at the beginning of the frame.
	//virtual void OnUpdate(double dt) = 0;
	/// Called when all gameobjects have been updated.
	virtual void OnRender(void) = 0;
private:
	CRenderer* m_renderer;
};

#endif