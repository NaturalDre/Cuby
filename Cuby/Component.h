#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class IGameObject;
class IComponent
{
public:
	enum { UNKNOWN, SCRIPT, RENDERER, AUDIO, PHYSICS, INPUT};

	IComponent(const std::string& name, size_t type): m_name(name), m_enabled(true), m_gameObject(nullptr), m_type(type) { }
	virtual ~IComponent(void) { m_gameObject = nullptr; }

	void SetGameObject(IGameObject* gameObject) { m_gameObject = gameObject; }	

	const std::string& GetName(void) const { return m_name; }
	IGameObject* GetGameObject(void) const { return m_gameObject; }
	void SetEnabled(bool isEnabled) { m_enabled = isEnabled; }
	bool IsEnabled(void) const { return m_enabled; }
	int GetType(void) const { return m_type; }

	// Wrappers for abstract functions
	void Start(void) { OnStart(); }
	void Update(double dt) { OnUpdate(dt); }
	void FixedUpdate(void) { OnFixedUpdate(); }

protected:
	/// Called when the scene is started.
	virtual void OnStart(void) = 0;
	/// Called when the scene is updated.
	virtual void OnUpdate(double dt) = 0;
	/// Called every fixed timestep.
	virtual void OnFixedUpdate(void) = 0;

private:
	std::string m_name;			/// Name of this component
	bool m_enabled;				/// Is it enabled?
	IGameObject* m_gameObject;	/// GameObject that owns this component.
	size_t m_type;				/// The type of component

};

#endif