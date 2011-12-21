#include "image.h"

Image::Image(std::string filename)
{
	SDL_Surface *otimized = NULL;

	image = IMG_Load(filename.c_str());

	if (image != NULL)
	{
		otimized = SDL_DisplayFormat(image);

		if (otimized != NULL) {
			SDL_FreeSurface(image);
			image = otimized;
		}
	}
}

Image::~Image()
{
	SDL_FreeSurface(image);
}

const SDL_Surface *Image::getSurface()
{
	return image;
}
