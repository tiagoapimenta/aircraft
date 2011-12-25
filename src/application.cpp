#include "application.h"

Application::Application()
{
	screen = new Screen();
	event = new Event();
	audio = new Audio();
	world = NULL;
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
	world = new World(this);

	new Enemy(this, 1, 1, 15, -5, 1);

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
	for (std::set<IUpdatable*>::iterator it = updaters.begin() ; it != updaters.end(); it++ )
	{
		(*it)->update();
	}
}

void Application::addUpdater(IUpdatable *updater)
{
	updaters.insert(updater);
}

void Application::removeUpdater(IUpdatable *updater)
{
	for (std::set<IUpdatable*>::iterator it = updaters.begin() ; it != updaters.end(); it++ )
	{
		if (*it == updater)
		{
			updaters.erase(it);
			break;
		}
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

void Application::startCounter()
{
	timer = SDL_GetTicks();
}

void Application::waitFPS()
{
	Uint32 elapsed_time = SDL_GetTicks() - timer;

	if (elapsed_time < TIME_PER_FRAME) SDL_Delay(TIME_PER_FRAME - elapsed_time);
	else if (elapsed_time != TIME_PER_FRAME) std::cerr << "Overlapped time: " << elapsed_time - TIME_PER_FRAME << std::endl;

	timer += elapsed_time;
}
