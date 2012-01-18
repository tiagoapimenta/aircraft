#include "screen.h"

Screen::Screen()
{
	if (SDL_Init (SDL_INIT_VIDEO) == -1) throw "Couldn't init video.";

	screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if (screen == NULL) throw "Couldn't create a video surface.";

	if (TTF_Init() == -1) throw "Couldn't init TTF support.";

	SDL_WM_SetCaption (SCREEN_TITLE, NULL);
	SDL_ShowCursor (SDL_DISABLE);
}

Screen::~Screen()
{
	TTF_Quit();
}

void Screen::blitImage (int x, int y, Image *source)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface (source->getSurface(), NULL, screen, &offset);
}

void Screen::clear()
{
	SDL_FillRect (screen, &screen->clip_rect, SDL_MapRGB (screen->format, 0, 0, 0));
}

void Screen::render()
{
	clear();

	for (int k = 0; k < MAX_LAYERS; k++)
	{
		for (std::set<IDrawable*>::iterator it = drawers[k].begin() ; it != drawers[k].end(); it++)
		{
			(*it)->draw();
		}
	}

	SDL_Flip (screen);
}

void Screen::addDrawer (int layer, IDrawable *drawer)
{
	if (layer < 0 || layer > MAX_LAYERS) throw "Out of range";

	drawers[layer].insert (drawer);
}

void Screen::removeDrawer (int layer, IDrawable *drawer)
{
	if (layer < 0 || layer > MAX_LAYERS) throw "Out of range";

	drawers[layer].erase (drawer);
}
