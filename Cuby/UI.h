#ifndef UI_H
#define UI_H

#include <Gwen\Gwen.h>
#include <Gwen\Skins\Simple.h>
#include <Gwen\Skins\TexturedBase.h>
#include <Gwen\Renderers\Allegro.h>
#include <Gwen\Input\Allegro.h>
class CUI
{
protected:
	void SetupMenus(void);

public:
	CUI(void);
	~CUI(void);

	Gwen::Controls::Canvas* GetCanvas(void) const { return m_pCanvas; }
	Gwen::Renderer::Allegro* GetRenderer(void) const { return m_pRenderer; }
	const Gwen::Skin::TexturedBase& GetSkin(void) const { return m_skin; }
	Gwen::Input::Allegro& GetInput(void) { return m_allegroInput; }

private:
	Gwen::Controls::Canvas* m_pCanvas;
	Gwen::Renderer::Allegro* m_pRenderer;
	Gwen::Skin::TexturedBase m_skin;
	Gwen::Input::Allegro m_allegroInput;
};

#endif