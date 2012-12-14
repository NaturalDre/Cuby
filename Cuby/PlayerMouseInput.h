#ifndef PLAYERMOUSEINPUT_H
#define PLAYERMOUSEINPUT_H

#include "InputComponent.h"

class CPlayer;
class CTTTBoard;

class CPlayerMouseInput: public IInputComponent
{
public:
	CPlayerMouseInput(CPlayer* player, CTTTBoard* m_board);
protected:
	void Handle(const ALLEGRO_EVENT& ev);

private:
	CPlayer* m_player;
	CTTTBoard* m_board;
};
#endif