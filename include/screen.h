#ifndef SCREEN_H
#define SCREEN_H

#include "core.h"

class Image;

class Screen
{
public:
	static Screen& getInstance();

	void blitImage(int x, int y, Image &source);
	void clear();
	void render();

protected:
private:
	static Screen *instance;
	SDL_Surface *screen;

	Screen();
};

#endif // SCREEN_H

