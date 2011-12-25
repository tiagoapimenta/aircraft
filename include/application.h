#ifndef APPLICATION_H
#define APPLICATION_H

#include "core.h"

#define FRAMES_PER_SECOND 40
#define TIME_PER_FRAME (1000 / FRAMES_PER_SECOND)

class Screen;
class Event;
class World;

class Application
{
public:
	static Application* getInstance();
	int gameLoop();
	void addUpdater(IUpdatable *updater);
	void removeUpdater(IUpdatable *updater);
	Screen* getScreen();
	Event* getEvent();
	World* getWorld();
	void computePoints(int points);

protected:
private:
	static Application *instance;
	Screen *screen;
	Event *event;
	World *world;
	Uint32 timer;
	int points;

	std::set<IUpdatable*> updaters;

	Application();

	void startCounter();
	void waitFPS();
	void update();
	void quit();
};

#endif // APPLICATION_H
