#ifndef SCREEN_H
#define SCREEN_H

#include "core.h"

#define MAX_LAYERS 5

class Image;

class Screen
{
public:
	static Screen* getInstance();

	void blitImage(int x, int y, Image *source);
	void clear();
	void render();
	void addDrawer(int layer, IDrawable *drawer);
	void removeDrawer(int layer, IDrawable *drawer);

protected:
private:
	static Screen *instance;

	SDL_Surface *screen;
	std::vector<IDrawable*> drawers[MAX_LAYERS];

	Screen();
};

#endif // SCREEN_H

