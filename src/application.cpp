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
	Aircraft *aircraft = new Aircraft(this);

	startCounter();

	while (event->poll())
	{
		// Logic?
		aircraft->update();

		// Rendering
		screen->clear();
		aircraft->draw();
		screen->render();

		waitFPS();
	}

	delete aircraft;

	quit();

	return 0;
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
