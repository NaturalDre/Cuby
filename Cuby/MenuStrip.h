#ifndef MENUSTRIP_H
#define MENUSTRIP_H

#include <Gwen\Gwen.h>
#include <Gwen\Controls\MenuStrip.h>

class CApplication;
class CMenuStrip: public Gwen::Controls::MenuStrip
{
public:
	CMenuStrip(Gwen::Controls::Canvas* pCanvas, CApplication* app);
	~CMenuStrip(void);

	void OnNewCheckersClicked(Gwen::Controls::Base* pControl);
	void OnNewTTTClicked(Gwen::Controls::Base* pControl);
	void OnQuitClicked(Gwen::Controls::Base* pControl);
private:
	Gwen::Controls::MenuItem* m_pFileMenu;
	CApplication* m_app;
};

#endif