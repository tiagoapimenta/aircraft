#include "event.h"

Event *Event::instance = NULL;

Event::Event()
{
	//ctor
}

Event* Event::getInstance()
{
	if (!instance) instance = new Event();

	return instance;
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
			int length = keyEvents.size();
			for (int i = 0; i < length; i++)
			{
				keyEvents[i]->keyDown(event.key.keysym.sym);
			}
			break;
		}
		case SDL_KEYUP:
		{
			int length = keyEvents.size();
			for (int i = 0; i < length; i++)
			{
				keyEvents[i]->keyUp(event.key.keysym.sym);
			}
			break;
		}
		}
	}

	int length = updaters.size();
	for (int i = 0; i < length; i++)
	{
		updaters[i]->update();
	}

	return !quit;
}

void Event::addKeyEvent(IKeyEventHandleable *keyEvent)
{
	keyEvents.push_back(keyEvent);
}

void Event::removeKeyEvent(IKeyEventHandleable *keyEvent)
{
	for (std::vector<IKeyEventHandleable*>::iterator it = keyEvents.begin() ; it < keyEvents.end(); it++ )
	{
		if (*it == keyEvent)
		{
			keyEvents.erase(it);
			break;
		}
	}
}

void Event::addUpdater(IUpdatable *updater)
{
	updaters.push_back(updater);
}

void Event::removeUpdater(IUpdatable *updater)
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
