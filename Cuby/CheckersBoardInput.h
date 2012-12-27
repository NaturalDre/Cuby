#ifndef CHECKERSBOARDINPUT_H
#define CHECKERSBOARDINPUT_H

#include "InputComponent.h"

class CCheckersBoard;
class CCheckersBoardInput: public IInputComponent
{
public:
	CCheckersBoardInput(CCheckersBoard* board);
	~CCheckersBoardInput(void);

protected:
	/// Called when the scene is started.
	void OnStart(void) { }
	/// Called when the scene is updated.
	void OnUpdate(double dt) { }
	/// Called every fixed timestep.
	void OnFixedUpdate(void) { }

	void Handle(const ALLEGRO_EVENT& ev);

private:
	CCheckersBoard* m_board;
};

#endif