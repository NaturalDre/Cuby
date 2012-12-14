#include <iostream>
#include "Application.h"
int main(void)
{
	CApplication app;
	if (!app.Init())
		return app.Run();
	return EXIT_FAILURE;
};