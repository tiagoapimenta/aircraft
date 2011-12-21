#include "main.h"

int main(int argc, char *argv[])
{
	Screen screen = Screen::getInstance();
	Util util = Util::getInstance();
	Event event = Event::getInstance();
	Image *aircaft = NULL;

	aircaft = new Image(IMG_NAVE);

	util.startCounter();

	while (event.poll())
	{
		// Logic?

		// Rendering
		screen.clear();
		screen.blitImage(10, 10, *aircaft);
		screen.render();

		util.waitFPS();
	}

	delete aircaft;

	util.quit();
	return 0;
}

