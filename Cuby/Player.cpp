#include "Player.h"
#include "Bitmap.h"

CPlayer::CPlayer(const std::string& name, CEngine* engine)
	: IGameObject(name, engine)
	, m_gamePiece(nullptr)
	, m_wins(0)
	, m_losses(0)
	, m_draws(0)
{

}

CPlayer::~CPlayer(void)
{

}

void CPlayer::Start(void)
{
	IGameObject::Start();
	m_gamePiece = new CBitmap(m_gamePieceFilename, 0);
	m_gamePiece->Load();
	if (!m_gamePiece->IsLoaded())
	{
		m_gamePiece->Unload();
		delete m_gamePiece;
		m_gamePiece = nullptr;
	}
}

void CPlayer::SetGamePiece(const std::string& filename)
{
	m_gamePieceFilename = filename;
}