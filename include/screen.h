#ifndef SCREEN_H
#define SCREEN_H

#include "core.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_BPP 32

#define SCREEN_TITLE "Aircraft Burner"

#define MAX_LAYERS 6

class Image;

class Screen
{
public:
	Screen();
	~Screen();

	void blitImage(int x, int y, Image *source);

	void render();

	void addDrawer(int layer, IDrawable *drawer);
	void removeDrawer(int layer, IDrawable *drawer);

protected:
private:
	SDL_Surface *screen;
	std::set<IDrawable*> drawers[MAX_LAYERS];

	void clear();
};

#endif // SCREEN_H

