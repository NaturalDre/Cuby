#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include <Box2D\Common\b2Math.h>

class IComponent;
class CEngine;
class IGameObject
{
public:
	IGameObject(const std::string& name, CEngine* engine/*, float x, float y, float angle*/);
	virtual ~IGameObject(void);

	const b2Transform& GetTransform(void) const { return m_transform; }
	const std::string GetName(void) const { return m_name; }
	/// Find an attached component by its name.
	IComponent* GetComponent(const std::string& name) const;
	IComponent* GetComponentAt(unsigned int index) const;
	bool AddComponent(IComponent* component);
	bool RemoveComponent(const std::string& name);
	bool RemoveComponentAt(unsigned int index);
	CEngine* GetEngine(void) const { return m_engine; }

	/// Initializes this object by starting each of its attached components.
	/// @note When you override this function, make sure to call IGameObject::Start()
	///	if you want Start() to be called on the components.
	virtual void Start(void);
	/// Updates the game object by updating each of the components attached to it.
	/// @note When you override this function, make sure to call IGameObject::Update(dt)
	///	if you want Update(dt) to be called on the components.
	virtual void Update(double dt);
	/// Called 60 times a second. Used to updated physics related game logic.
	/// @note When you override this function, make sure to call IGameObject::FixedUpdate()
	///	if you want FixedUpdate() to be called on the components.
	virtual void FixedUpdate(void);
private:
	std::string m_name;						/// A unique name for this game object.
	b2Transform m_transform;				/// This object's transform.
	std::vector<IComponent*> m_components;	/// A list of attached components.
	CEngine* m_engine;
};

#endif