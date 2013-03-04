#ifndef APPLICATION_H
#define APPLICATION_H

class CEngine;
class CPlayer;
class IGameBoard;
class IRenderComponent;
class IInputComponent;

class CApplication
{
public:
	CApplication(void);
	~CApplication(void);

	int Init(void);
	int Run(void);

	void StartNewCheckers(void);
	void StartNewTicTacToe(void);
	void Quit(void);
private:
	CEngine* m_engine;
	IGameBoard* m_pGameBoard;
	IRenderComponent* m_pBoardRender;
	IInputComponent* m_pBoardInput;

};

#endif