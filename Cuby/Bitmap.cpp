#include "Bitmap.h"
#include <allegro5\allegro5.h>


unsigned int CBitmap::GetWidth(void) const
{
	if (m_data)
		return al_get_bitmap_width(m_data);
	return 0;
}

unsigned int CBitmap::GetHeight(void) const
{
	if (m_data)
		return al_get_bitmap_height(m_data);
	return 0;
}

void CBitmap::ConvertMaskToAlpha(size_t r, size_t g, size_t b)
{
	if (IsLoaded())
		al_convert_mask_to_alpha(m_data, al_map_rgb(r,g,b));
}

void CBitmap::OnLoad(void)
{
	if (IsLoaded())
		Unload();
	// Allegro doesn't want us trying to load an empty filename
	if (!GetFilename().empty())
		m_data = al_load_bitmap(GetFilename().c_str());
	// If we get nullptr, then it did not load. Otherwise, it loaded.
	SetLoaded(m_data);
}

void CBitmap::OnUnload(void)
{
	if (IsLoaded())
	{
		al_destroy_bitmap(m_data);
		m_data = nullptr;
		SetLoaded(false);
	}
}