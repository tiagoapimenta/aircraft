#ifndef SCREEN_H
#define SCREEN_H

#include "core.h"

class Screen
{
public:
	static Screen& getInstance();

	void blitSurface(int x, int y, SDL_Surface *source);
	void clear();
	void render();

protected:

private:
	static Screen *instance;
	SDL_Surface *screen;

	Screen();
};

#endif // SCREEN_H

