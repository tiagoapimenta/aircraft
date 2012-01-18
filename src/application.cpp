#include "application.h"

Application::Application()
{
	screen = new Screen();
	event = new Event();
	audio = new Audio();
	world = NULL;

	srand (time (NULL));
}

Application::~Application()
{
	Image::clearCache();
	Font::clearCache();

	delete event;
	delete screen;
	delete audio;

	SDL_Quit();
}

int Application::gameLoop()
{
	world = new World (this, 1);

	startCounter();

	while (event->poll())
	{
		update();

		screen->render();

		waitFPS();
	}

	delete world;
	world = NULL;

	return 0;
}

void Application::update()
{
	for (std::map<IUpdatable*, bool>::iterator it = updaters.begin() ; it != updaters.end(); it++)
	{
		if (!paused || it->second) it->first->update();
	}
}

void Application::addUpdater (IUpdatable *updater, bool continue_on_pause)
{
	updaters.insert (std::make_pair (updater, continue_on_pause)); // TODO: maybe updaters[updater] = continue_on_pause;
}

void Application::removeUpdater (IUpdatable *updater)
{
	if (updaters.count (updater) > 0)
	{
		updaters.erase (updater);
	}
}

Screen* Application::getScreen()
{
	return screen;
}

Event* Application::getEvent()
{
	return event;
}

Audio* Application::getAudio()
{
	return audio;
}

World* Application::getWorld()
{
	return world;
}

bool Application::isPaused()
{
	return paused;
}

void Application::pause (bool pause)
{
	paused = pause;

	if (paused)
	{
		playing_paused_music = audio->isMusicPlaying();

		if (playing_paused_music) audio->pauseMusic();
	}
	else if (playing_paused_music) audio->playMusic();
}

void Application::startCounter()
{
	timer = SDL_GetTicks();
}

void Application::waitFPS()
{
	Uint32 elapsed_time = SDL_GetTicks() - timer;

	if (elapsed_time < TIME_PER_FRAME - TIME_PER_FRAME_OFF) SDL_Delay (TIME_PER_FRAME - TIME_PER_FRAME_OFF - elapsed_time);
	else if (elapsed_time > TIME_PER_FRAME) std::cerr << "Overlapped time: " << elapsed_time - TIME_PER_FRAME << std::endl;

	timer += elapsed_time;
}
