#ifndef APPLICATION_H
#define APPLICATION_H

#include "core.h"

#define FRAMES_PER_SECOND 40
#define TIME_PER_FRAME (1000 / FRAMES_PER_SECOND)
#define TIME_PER_FRAME_OFF (TIME_PER_FRAME / 4) // 25% of time_per_frame is margin of error

class Screen;
class Event;
class Audio;
class World;

class Application
{
public:
	Application();
	~Application();

	int gameLoop();
	void addUpdater(IUpdatable *updater, bool continue_on_pause = false); // TODO: AddUpdateListener
	void removeUpdater(IUpdatable *updater);
	Screen* getScreen();
	Event* getEvent();
	Audio* getAudio();
	World* getWorld();
	void computePoints(int points);
	bool isPaused();
	void pause(bool pause);

protected:
private:
	Screen *screen;
	Event *event;
	Audio *audio;
	World *world;
	Uint32 timer;
	bool paused;
	bool playing_paused_music;

	std::map<IUpdatable*, bool> updaters;

	void startCounter();
	void waitFPS();
	void update();
	void quit();
};

#endif // APPLICATION_H
