#include "screen.h"

Screen *Screen::instance = NULL;

Screen::Screen()
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1) throw "Couldn't init video.";
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (screen == NULL) throw "Couldn't create a video surface.";
	SDL_WM_SetCaption(SCREEN_TITLE, NULL);
	SDL_ShowCursor(SDL_DISABLE);
}

Screen* Screen::getInstance()
{
	if (!instance) instance = new Screen();

	return instance;
}

void Screen::blitImage(int x, int y, Image *source)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source->getSurface(), NULL, screen, &offset);
}

void Screen::clear()
{
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
}

void Screen::render()
{
	for (int k = 0; k < MAX_LAYERS; k++)
	{
		int length = drawers[k].size();
		for (int i = 0; i < length; i++)
		{
			drawers[k][i]->draw();
		}
	}

	SDL_Flip(screen);
}

void Screen::addDrawer(int layer, IDrawable *drawer)
{
	if (layer < 0 || layer > MAX_LAYERS) throw "Out of range";

	drawers[layer].push_back(drawer);
}

void Screen::removeDrawer(int layer, IDrawable *drawer)
{
	if (layer < 0 || layer > MAX_LAYERS) throw "Out of range";

	for (std::vector<IDrawable*>::iterator it = drawers[layer].begin() ; it < drawers[layer].end(); it++ )
	{
		if (*it == drawer)
		{
			drawers[layer].erase(it);
			break;
		}
	}
}
