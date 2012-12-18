#include "Application.h"
#include "Engine.h"
#include "TTTBoard.h"
#include "TTTBoardRender.h"
#include "TTTBoardInput.h"
#include "Player.h"
#include "PlayerKeyboardInput.h"
#include "PlayerMouseInput.h"
#include "Debug.h"
#include "CheckersBoard.h"

CApplication::CApplication(void)
	: m_engine(nullptr)
{

}

CApplication::~CApplication(void)
{

}

int CApplication::Init(void)
{
	m_engine = new CEngine;
	if (m_engine->Init())
		return -1;
	return 0;
}

// Most of this is just test code, so I don't bother freeing some stuff.
// Mainly using it to start instances of the board games for testing.
int CApplication::Run(void)
{
	CCheckersBoard* board = new CCheckersBoard(m_engine);
	m_engine->SetGameBoard(board);
	board->StartNewMatch();
	//CTTTBoard* board = new CTTTBoard(m_engine);
	//m_engine->SetGameBoard(board);

	//// Add the board components.
	//// TODO: Figure out if I'm even using CTTTBoardInput. I *think* each player's
	//// InputComponent should take care of everything. We may use it for non player-
	//// specific stuff.
	//auto input = new CTTTBoardInput(board);
	//auto render = new CTTTBoardRender(board, m_engine->GetRenderer());
	//// This is different from adding a component to a game object. 
	//// We add it to the engine so the engine can pass it input information. 
	//m_engine->AddInputComponent(input);


	//board->AddComponent(input);
	//board->AddComponent(render);

	////board->StartNewMatch(m_player1, m_player2);

	NOTE("Press R to start a new game.");
	const int ret = m_engine->Run();


	//delete input; input = nullptr;
	//delete render; render = nullptr;

	return ret;
}