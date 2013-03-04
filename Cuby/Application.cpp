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
#include "CheckersBoardRender.h"
#include "CheckersBoardInput.h"
#include "MenuStrip.h"
#include "UI.h"

CApplication::CApplication(void)
	: m_engine(nullptr)
	, m_pGameBoard(nullptr)
	, m_pBoardRender(nullptr)
	, m_pBoardInput(nullptr)
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

	new CMenuStrip(m_engine->GetUI()->GetCanvas(), this);
	return 0;
}

// Most of this is just test code, so I don't bother freeing some stuff.
// Mainly using it to start instances of the board games for testing.
int CApplication::Run(void)
{
	//CCheckersBoard* board = new CCheckersBoard(m_engine);
	//auto render = new CCheckersBoardRender(board, m_engine->GetRenderer());
	//auto input = new CCheckersBoardInput(board);
	//board->AddComponent(render);
	//board->AddComponent(input);
	//m_engine->AddInputComponent(input);
	//m_engine->SetGameBoard(board);
	//board->StartNewMatch();




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

void CApplication::StartNewCheckers(void)
{
	//CCheckersBoard* board = new CCheckersBoard(m_engine);
	//auto render = new CCheckersBoardRender(board, m_engine->GetRenderer());
	//render->Start();
	//auto input = new CCheckersBoardInput(board);
	//input->Start();
	//board->AddComponent(render);
	//board->AddComponent(input);
	//m_engine->AddInputComponent(input);
	//m_engine->SetGameBoard(board);

	//board->SetY(100);
	//board->StartNewMatch();

	if (m_pGameBoard && m_pGameBoard->GetName() == "Checkers")
	{
		if (m_pGameBoard->EndCurrentMatch())
			m_pGameBoard->StartNewMatch();
	}
	else
	{
		delete m_pGameBoard;
		delete m_pBoardRender;
		delete m_pBoardInput;
		m_engine->RemoveInputComponent(m_pBoardInput);
		{
			CCheckersBoard* pCheckersBoard = new CCheckersBoard(m_engine);
			//pCheckersBoard->Start();
			pCheckersBoard->SetX(0);
			pCheckersBoard->SetY(50);

			CCheckersBoardRender* pCheckersBoardRender = new CCheckersBoardRender(pCheckersBoard, m_engine->GetRenderer());
			pCheckersBoardRender->Start();

			CCheckersBoardInput* pCheckersBoardInput = new CCheckersBoardInput(pCheckersBoard);
			pCheckersBoardInput->Start();

			m_pGameBoard = pCheckersBoard;
			m_pBoardRender = pCheckersBoardRender;
			m_pBoardInput = pCheckersBoardInput;
		}
		m_engine->AddInputComponent(m_pBoardInput);
		m_engine->SetGameBoard(m_pGameBoard);
		m_pGameBoard->StartNewMatch();
	}
}

void CApplication::StartNewTicTacToe(void)
{
	if (m_pGameBoard && m_pGameBoard->GetName() == "TTT")
	{
		if (m_pGameBoard->EndCurrentMatch())
			m_pGameBoard->StartNewMatch();
	}
	else
	{
		delete m_pGameBoard;
		delete m_pBoardRender;
		delete m_pBoardInput;
		m_engine->RemoveInputComponent(m_pBoardInput);
		{
			CTTTBoard* pTTTBoard = new CTTTBoard(m_engine);
			pTTTBoard->Start();
			pTTTBoard->SetX(0);
			pTTTBoard->SetY(50);

			CTTTBoardRender* pTTTBoardRender = new CTTTBoardRender(pTTTBoard, m_engine->GetRenderer());
			pTTTBoardRender->Start();

			CTTTBoardInput* pTTTBoardInput = new CTTTBoardInput(pTTTBoard);
			pTTTBoardInput->Start();

			m_pGameBoard = pTTTBoard;
			m_pBoardRender = pTTTBoardRender;
			m_pBoardInput = pTTTBoardInput;

		}
		m_engine->AddInputComponent(m_pBoardInput);
		m_engine->SetGameBoard(m_pGameBoard);
		m_pGameBoard->StartNewMatch();
	}
}

void CApplication::Quit(void)
{
	m_engine->SetDone(true);
}