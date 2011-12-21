#include "util.h"

Util *Util::instance = NULL;

Util::Util()
{
	//ctor
}

Util &Util::getInstance()
{
	if (!instance) instance = new Util();

	return *instance;
}

SDL_Surface *Util::loadImage(std::string filename)
{
	SDL_Surface *image = NULL;
	SDL_Surface *otimized = NULL;

	image = IMG_Load(filename.c_str());

	if (image != NULL)
	{
		otimized = SDL_DisplayFormat(image);
		SDL_FreeSurface(image);
	}

	return otimized;
}

void Util::startCounter()
{
	timer = SDL_GetTicks();
}

void Util::waitFPS()
{
	elapsed_time = SDL_GetTicks() - timer;

	if (elapsed_time < TIME_PER_FRAME) SDL_Delay(TIME_PER_FRAME - elapsed_time);
	else if (elapsed_time != TIME_PER_FRAME) std::cerr << "Overlapped time: " << elapsed_time - TIME_PER_FRAME << std::endl;

	timer += elapsed_time;
}

void Util::quit()
{
	SDL_Quit();
}
