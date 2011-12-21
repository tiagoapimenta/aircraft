#ifndef SCREEN_H
#define SCREEN_H

#include "core.h"

class Image;

class Screen
{
public:
	Screen();

	void blitImage(int x, int y, Image &source);
	void clear();
	void render();

protected:

private:
	SDL_Surface *screen;
};

#endif // SCREEN_H

