#include <SDL/SDL.h>

int main (int argc, char* argv[]) {
	SDL_Surface* screen = NULL;
	SDL_Event event;
	bool quit = false;

	SDL_Init(SDL_INIT_VIDEO);

	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				{
					if (event.key.keysym.sym == SDLK_ESCAPE) quit = true;
					break;
				}
			}
		}

		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

		SDL_Flip(screen);
	}

	return 0;
}
