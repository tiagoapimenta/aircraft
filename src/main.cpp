#include "main.h"

int main (int argc, char *argv[]) {
	SDL_Surface *screen = NULL, *aircaft = NULL;
	SDL_Event event;
	bool quit = false;
	Uint32 fps_time = 0, elapsed_time = 0;

	SDL_Init(SDL_INIT_VIDEO);

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF);
	SDL_WM_SetCaption(SCREEN_TITLE, NULL);

	aircaft = load_image(IMG_NAVE);

	fps_time = SDL_GetTicks();

	while (!quit) {
		// Events
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

		// Logic

		// Rendering
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

		apply_surface(10, 10, aircaft, screen);

		SDL_Flip(screen);

		elapsed_time = SDL_GetTicks() - fps_time;
		//if (elapsed_time * FRAMES_PER_SECOND < 1000) SDL_Sleep((1000 - elapsed_time) / FRAMES_PER_SECOND);
	}

	SDL_FreeSurface(aircaft);
	SDL_Quit();
	return 0;
}

SDL_Surface *load_image(const char* filename) {
	SDL_Surface *image = NULL;
	SDL_Surface *otimized = NULL;

	image = IMG_Load(filename);
	if (image != NULL) {
		otimized = SDL_DisplayFormat(image);
		SDL_FreeSurface(image);
	}
	return otimized;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *target) {
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, target, &offset);
}
