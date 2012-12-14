#ifndef PLAYERKEYBOARDINPUT_H
#define PLAYERKEYBOARDINPUT_H

#include "InputComponent.h"

class CPlayer;
class CTTTBoard;

class CPlayerKeyboardInput: public IInputComponent
{
public:
	CPlayerKeyboardInput(CPlayer* player, CTTTBoard* m_board);
	~CPlayerKeyboardInput(void);

protected:
	void Handle(const ALLEGRO_EVENT& ev);

private:
	CPlayer* m_player;
	CTTTBoard* m_board;
};
#endif