#include "application.h"

Application *Application::instance = NULL;

Application::Application()
{
	screen = &Screen::getInstance();
	event = &Event::getInstance();
}

Application& Application::getInstance()
{
	if (!instance) instance = new Application();

	return *instance;
}

int Application::gameLoop()
{
	Image *aircaft = NULL;

	aircaft = new Image(IMG_NAVE);

	startCounter();

	while (event->poll())
	{
		// Logic?

		// Rendering
		screen->clear();
		screen->blitImage(10, 10, *aircaft);
		screen->render();

		waitFPS();
	}

	delete aircaft;

	quit();

	return 0;
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
