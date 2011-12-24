#include "image.h"

Image::Image(std::string filename)
{
	SDL_Surface *otimized = NULL;

	image = IMG_Load(filename.c_str());

	if (image == NULL) throw "Image not found.";

	otimized = SDL_DisplayFormat(image);

	if (otimized != NULL) {
		SDL_FreeSurface(image);
		image = otimized;
	}
}

Image::~Image()
{
	SDL_FreeSurface(image);
}

SDL_Surface *Image::getSurface()
{
	return image;
}

int Image::getWidth()
{
	return image->w;
}

int Image::getHeight()
{
	return image->h;
}
