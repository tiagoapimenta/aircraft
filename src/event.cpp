#include "event.h"

Event *Event::instance = NULL;

Event::Event()
{
	//ctor
}

Event& Event::getInstance()
{
	if (!instance) instance = new Event();

	return *instance;
}

bool Event::poll()
{
	SDL_Event event;
	bool quit = false;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
		{
			if (event.key.keysym.sym == SDLK_ESCAPE) quit = true;
			break;
		}
		}
	}

	return !quit;
}
