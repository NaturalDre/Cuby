#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

class CAssetManager
{
public:
	static CAssetManager* Instance(void) { if (!instance) instance = new CAssetManager; return instance; }
protected:
	CAssetManager(void);
	~CAssetManager(void);

private:
	static CAssetManager* instance;
	size_t m_curScene;
	size_t m_loadedAssetCount;
};
#endif