#include "application.h"

Application *Application::instance = NULL;

Application::Application()
{
	screen = Screen::getInstance();
	event = Event::getInstance();
}

Application* Application::getInstance()
{
	if (!instance) instance = new Application();

	return instance;
}

int Application::gameLoop()
{
	World *world = new World(this);

	startCounter();

	while (event->poll())
	{
		update();

		screen->render();

		waitFPS();
	}

	delete world;

	quit();

	return 0;
}

void Application::update()
{
	int length = updaters.size();
	for (int i = 0; i < length; i++)
	{
		updaters[i]->update();
	}
}

void Application::addUpdater(IUpdatable *updater)
{
	updaters.push_back(updater);
}

void Application::removeUpdater(IUpdatable *updater)
{
	for (std::vector<IUpdatable*>::iterator it = updaters.begin() ; it < updaters.end(); it++ )
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

void Application::quit()
{
	SDL_Quit();
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
