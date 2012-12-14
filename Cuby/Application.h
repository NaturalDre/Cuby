#ifndef APPLICATION_H
#define APPLICATION_H

class CEngine;
class CPlayer;
class CApplication
{
public:
	CApplication(void);
	~CApplication(void);

	int Init(void);
	int Run(void);
private:
	CEngine* m_engine;
};

#endif