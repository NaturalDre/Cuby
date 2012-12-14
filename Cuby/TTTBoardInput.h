#ifndef TTTBOARDINPUT_H
#define TTTBOARDINPUT_H

#include "InputComponent.h"
class CPlayer;
class CTTTBoard;
class CTTTBoardInput: public IInputComponent
{
public:
	CTTTBoardInput(CTTTBoard* board): m_board(board) { }
	void Handle(const ALLEGRO_EVENT& ev);

private:
	CTTTBoard* m_board;
	CPlayer* m_keyboardPlayer;
	CPlayer* m_mousePlayer;
};

#endif