#include "GameObject.h"
#include "Component.h"
#include "Engine.h"

IGameObject::IGameObject(const std::string& name, CEngine* engine/*, float x, float y, float angle*/)
	: m_engine(engine)
	//, m_name(name)
	//, m_transform(b2Vec2(x, y), b2Rot(angle))
{
	assert(GetEngine() != nullptr);
	GetEngine()->AddGameObject(this);
}


IGameObject::~IGameObject(void)
{
	assert(GetEngine() != nullptr);
	GetEngine()->RemoveGameObject(this);
	//for (unsigned int i = 0; i < m_components.size(); ++i)
	//	m_components[i]->e
}


IComponent* IGameObject::GetComponent(const std::string& name) const
{
	for (unsigned int i = 0; i < m_components.size(); ++i)
		if (m_components[i]->GetName() == name)
			return m_components[i];
	return nullptr;
}

IComponent* IGameObject::GetComponentAt(unsigned int index) const
{
	if (index < m_components.size())
		return m_components[index];
	return nullptr;
}

bool IGameObject::AddComponent(IComponent* component)
{
	for (unsigned int i = 0; i < m_components.size(); ++i)
		if (!component || (m_components[i] == component) || (m_components[i]->GetName() == component->GetName()))
			return false;

	m_components.push_back(component);
	component->SetGameObject(this);
	return true;
}

bool IGameObject::RemoveComponent(const std::string& name)
{
	for (unsigned int i = 0; i < m_components.size(); ++i)
	{
		if (m_components[i]->GetName() == name)
		{
			m_components.erase(m_components.begin() + i);
			return true;
		}
	}
	return false;
}

bool IGameObject::RemoveComponentAt(unsigned int index)
{
	if (index < m_components.size())
	{
		m_components.erase(m_components.begin() + index);
		return true;
	}
	return false;
}

void IGameObject::Start(void)
{
	// Iterate over all components, initializing each component if it is enabled.
	for (unsigned int i = 0; i < m_components.size(); ++i)
	{
		if (m_components[i]->IsEnabled())
			m_components[i]->Start();
	}
}

void IGameObject::Update(double dt)
{
	// Iterate over all components, updating each component if it is enabled.
	for (unsigned int i = 0; i < m_components.size(); ++i)
	{
		if (m_components[i]->IsEnabled())
			m_components[i]->Update(dt);
	}
}

void IGameObject::FixedUpdate(void)
{
	// Iterate over all components, updating each component if it is enabled.
	for (unsigned int i = 0; i < m_components.size(); ++i)
	{
		if (m_components[i]->IsEnabled())
			m_components[i]->FixedUpdate();
	}
}