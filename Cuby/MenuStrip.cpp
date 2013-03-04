#include "MenuStrip.h"
#include "Application.h"

CMenuStrip::CMenuStrip(Gwen::Controls::Canvas* pCanvas, CApplication* app)
	: Gwen::Controls::MenuStrip(pCanvas)
	, m_pFileMenu(nullptr)
	, m_app(app)
{
	Gwen::Controls::MenuItem* m_pFileMenu = AddItem(L"File");
	auto pNewRoot = m_pFileMenu->GetMenu()->AddItem( L"New", L"test16.png", "Ctrl + N");
	pNewRoot->GetMenu()->AddItem("Checkers")->SetAction(this, &CMenuStrip::OnNewCheckersClicked);
	pNewRoot->GetMenu()->AddItem("Tic Tac Toe")->SetAction(this, &CMenuStrip::OnNewTTTClicked);
	m_pFileMenu->GetMenu()->AddItem(L"Quit", "", "Ctrl+Q")->SetAction(this, &CMenuStrip::OnQuitClicked);
}

CMenuStrip::~CMenuStrip(void)
{

}

void CMenuStrip::OnNewCheckersClicked(Gwen::Controls::Base* pControl)
{
	if (m_app)
		m_app->StartNewCheckers();
}

void CMenuStrip::OnNewTTTClicked(Gwen::Controls::Base* pControl)
{
	if (m_app)
		m_app->StartNewTicTacToe();
}

void CMenuStrip::OnQuitClicked(Gwen::Controls::Base* pControl)
{
	if (m_app)
		m_app->Quit();
}