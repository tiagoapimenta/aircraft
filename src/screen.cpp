#include "screen.h"

Screen *Screen::instance = NULL;

Screen::Screen()
{
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption(SCREEN_TITLE, NULL);
}

Screen& Screen::getInstance()
{
	if (!instance) instance = new Screen();

	return *instance;
}

void Screen::blitSurface(int x, int y, SDL_Surface *source)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, screen, &offset);
}

void Screen::clear()
{
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
}

void Screen::render()
{
	SDL_Flip(screen);
}
