#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "Component.h"

union ALLEGRO_EVENT;
class IInputComponent: public IComponent
{
public:
	IInputComponent(const std::string& name = "Input Component"): IComponent(name, IComponent::INPUT) { }
	virtual void Handle(const ALLEGRO_EVENT& ev) = 0;

protected:
	/// Called when the scene is started.
	void OnStart(void) { }
	/// Called when the scene is updated.
	void OnUpdate(double dt) { }
	/// Called every fixed timestep.
	void OnFixedUpdate(void) { }
private:
};
#endif