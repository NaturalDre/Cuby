#ifndef BITMAP_H
#define BITMAP_H

#include "Asset.h"

struct ALLEGRO_BITMAP;
class CBitmap: public IAsset
{
public:
	/// Initialize with data.
	/// @param filename The file that will be load when asked to.
	/// @param scene The scene this file should be loaded with.
	/// @note Does not load the file.
	CBitmap(const std::string& filename, size_t scene): IAsset(filename, IAsset::GRAPHICAL, scene), m_data(nullptr) { }	
	virtual ~CBitmap(void) { if (IsLoaded()) Unload(); }

	operator bool() const { return IsLoaded(); }

	unsigned int GetWidth(void) const;
	unsigned int GetHeight(void) const;
	void ConvertMaskToAlpha(size_t r, size_t g, size_t b);
	ALLEGRO_BITMAP* GetData(void) const { return m_data; }

protected:

	/// @note This does not free the previous data. You must do that. 
	/// I can't call Unload() from here or infinite recursion would occur.
	void SetData(ALLEGRO_BITMAP* data) { m_data = data; }
	void OnLoad(void);
	void OnUnload(void);

protected:
	ALLEGRO_BITMAP* m_data;
};

#endif