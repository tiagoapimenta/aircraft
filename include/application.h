#ifndef APPLICATION_H
#define APPLICATION_H

#include "core.h"

#define FRAMES_PER_SECOND 40
#define TIME_PER_FRAME (1000 / FRAMES_PER_SECOND)

class Screen;
class Event;

class Application
{
public:
	static Application* getInstance();
	int gameLoop();
	void addUpdater(IUpdatable *updater);
	void removeUpdater(IUpdatable *updater);
	Screen* getScreen();
	Event* getEvent();

protected:
private:
	static Application *instance;
	Screen *screen;
	Event *event;
	Uint32 timer;
	std::vector<IUpdatable*> updaters;

	Application();

	void startCounter();
	void waitFPS();
	void update();
	void quit();
};

#endif // APPLICATION_H
