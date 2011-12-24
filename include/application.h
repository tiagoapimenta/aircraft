#ifndef APPLICATION_H
#define APPLICATION_H

#include "core.h"

class Screen;
class Event;

class Application
{
public:
	static Application* getInstance();
	int gameLoop();
	Screen* getScreen();
	Event* getEvent();

protected:
private:
	static Application *instance;
	Screen *screen;
	Event *event;
	Uint32 timer;

	Application();
	void startCounter();
	void waitFPS();
	void quit();
};

#endif // APPLICATION_H
