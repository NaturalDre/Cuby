#include "AssetManager.h"

CAssetManager* CAssetManager::instance = nullptr;

CAssetManager::CAssetManager(void)
	: m_curScene(0)
	, m_loadedAssetCount(0)
{

}

CAssetManager::~CAssetManager(void)
{

}