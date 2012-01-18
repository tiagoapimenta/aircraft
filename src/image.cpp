#include "image.h"

std::map<std::string, ImageCounter> Image::images;

Image::Image (std::string filename)
{
	from_file = true;
	this->filename = filename;

	if (images.count (filename) > 0)
	{
		std::map<std::string, ImageCounter>::iterator it = images.find (filename);
		it->second.counter++;
		image = it->second.image;
		return;
	}

	SDL_Surface *otimized = NULL;

	image = IMG_Load (filename.c_str());

	if (image == NULL) throw "Image not found.";

	otimized = SDL_DisplayFormat (image);

	if (otimized != NULL)
	{
		SDL_FreeSurface (image);
		image = otimized;
	}

	ImageCounter image_counter;
	image_counter.image = image;
	image_counter.counter = 1;
	images.insert (std::make_pair (filename, image_counter));
}

Image::Image (SDL_Surface *image)
{
	from_file = false;
	this->image = image;
}

Image::~Image()
{
	if (from_file) images.find (filename)->second.counter--;
	else SDL_FreeSurface (image);
}

void Image::clearCache()
{
	for (std::map<std::string, ImageCounter>::iterator it = images.begin(); it != images.end(); it++)
	{
		if (it->second.counter == 0)
		{
			SDL_FreeSurface (it->second.image);
			images.erase (it); // TODO: Dangerous iterator usage. After erase the iterator is invalid so dereferencing it or comparing it with another iterator is invalid.
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
