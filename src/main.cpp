#include "main.h"

int main(int argc, char *argv[])
{
	Screen screen = Screen::getInstance();
	Util util = Util::getInstance();

	SDL_Surface *aircaft = NULL;
	SDL_Event event;
	bool quit = false;

	aircaft = util.loadImage(IMG_NAVE);

	util.startCounter();

	while (!quit)
	{
		// Events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
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
		screen.clear();
		screen.blitSurface(10, 10, aircaft);
		screen.render();

		util.waitFPS();
	}

	SDL_FreeSurface(aircaft);

	util.close();
	return 0;
}

