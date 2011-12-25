#include "event.h"

Event::Event()
{
	//ctor
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
			if (event.key.keysym.sym == SDLK_ESCAPE) quit = true; // TODO: remove it
			for (std::set<IKeyEventHandleable*>::iterator it = keyEvents.begin() ; it != keyEvents.end(); it++)
			{
				(*it)->keyDown(event.key.keysym.sym);
			}
			break;
		}
		case SDL_KEYUP:
		{
			for (std::set<IKeyEventHandleable*>::iterator it = keyEvents.begin() ; it != keyEvents.end(); it++)
			{
				(*it)->keyUp(event.key.keysym.sym);
			}
			break;
		}
		}
	}

	return !quit;
}

void Event::addKeyEvent(IKeyEventHandleable *keyEvent)
{
	keyEvents.insert(keyEvent);
}

void Event::removeKeyEvent(IKeyEventHandleable *keyEvent)
{
	for (std::set<IKeyEventHandleable*>::iterator it = keyEvents.begin() ; it != keyEvents.end(); it++)
	{
		if (*it == keyEvent)
		{
			keyEvents.erase(it);
			break;
		}
	}
}
