#include "RenderComponent.h"
#include "Renderer.h"
#include <assert.h>

IRenderComponent::IRenderComponent(const std::string& name, CRenderer* renderer)
	: IComponent(name, IComponent::RENDERER)
	, m_renderer(renderer)
{
	assert(m_renderer != nullptr);
	if (m_renderer)
		m_renderer->AddComponent(this);
}

IRenderComponent::~IRenderComponent(void)
{
	if (m_renderer)
		m_renderer->RemoveComponent(this);
}

//void IRenderComponent::OnStart(void)
//{
//
//}
//
//void IRenderComponent::OnUpdate(double dt)
//{
//
//}