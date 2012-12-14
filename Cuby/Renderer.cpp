#include "Renderer.h"
#include "RenderComponent.h"
#include <algorithm>

CRenderer::CRenderer(CEngine* engine)
	: m_engine(nullptr)
{

}

CRenderer::~CRenderer(void)
{

}

void CRenderer::AddComponent(IRenderComponent* component)
{
	// We don't want to add nullptr's to the list.
	if (!component)
		return;
	auto iter = std::find(m_renderList.begin(), m_renderList.end(), component);
	// We don't want to add duplicates to the list.
	if (iter == m_renderList.end())
		m_renderList.push_back(component);
}

void CRenderer::RemoveComponent(IRenderComponent* component)
{
	m_renderList.remove(component);
}

void CRenderer::Render(void)
{
	for (auto iter = m_renderList.begin(); iter != m_renderList.end(); ++iter)
	{	// If the component is enabled, then render.
		if ((*iter)->IsEnabled())
			(*iter)->Render();
	}
}