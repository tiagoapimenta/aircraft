#include "screen.h"

Screen::Screen()
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1) throw "Couldn't init video.";
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_DOUBLEBUF);
	if (screen == NULL) throw "Couldn't create a video surface.";
	SDL_WM_SetCaption(SCREEN_TITLE, NULL);
}

void Screen::blitImage(int x, int y, Image &source)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source.getSurface(), NULL, screen, &offset);
}

void Screen::clear()
{
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
}

void Screen::render()
{
	SDL_Flip(screen);
}
