#include "image.h"

std::map<std::string, ImageCounter*> Image::images;

Image::Image(std::string filename)
{
	this->filename = filename;
	if (images.count(filename) > 0)
	{
		std::map<std::string, ImageCounter*>::iterator it = images.find(filename);
		it->second->counter++;
		image = it->second->image;
		return;
	}

	SDL_Surface *otimized = NULL;

	image = IMG_Load(filename.c_str());

	if (image == NULL) throw "Image not found.";

	otimized = SDL_DisplayFormat(image);

	if (otimized != NULL)
	{
		SDL_FreeSurface(image);
		image = otimized;
	}

	ImageCounter *image_counter = new ImageCounter();
	image_counter->image = image;
	image_counter->counter = 1;

	images.insert(make_pair(filename, image_counter));
}

Image::~Image()
{
	images.find(filename)->second->counter--;
}

void Image::clearCache()
{
	for (std::map<std::string, ImageCounter*>::iterator it = images.begin(); it != images.end(); it++)
	{
		if (it->second->counter == 0)
		{
			SDL_FreeSurface(it->second->image);
			delete it->second;
			images.erase(it);
		}
	}
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
