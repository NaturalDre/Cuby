#ifndef ASSET_H
#define ASSET_H

#include <string>

class IAsset
{
public:
	enum { UNKNOWN = 0, GRAPHICAL, AUDIO, SCRIPT };

	IAsset(const std::string& filename, size_t type, unsigned int scene): m_filename(filename), m_type(type), m_scene(scene), m_loaded(false) { }
	virtual ~IAsset(void) { /*Unload();*/ }

	const std::string& GetFilename(void) const { return m_filename; }
	unsigned int GetType(void) const { return m_type; }
	unsigned int GetScene(void) const { return m_scene; }
	bool IsLoaded(void) const { return m_loaded; }
	void Load(void) { OnLoad(); }
	void Unload(void) { OnUnload(); }

protected:
	void SetLoaded(bool isLoaded) { m_loaded = isLoaded; }
	virtual void OnLoad(void) = 0;
	virtual void OnUnload(void) = 0;

private:
	std::string m_filename; /// Filename of this asset.
	size_t m_type; /// Numeric id for the type of asset this is.
	int m_scene; /// The scene this asset is associated with.
	bool m_loaded; /// Is this asset currently loaded?
};

#endif