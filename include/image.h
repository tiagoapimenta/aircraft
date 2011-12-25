#ifndef IMAGE_H
#define IMAGE_H

#include "core.h"

struct ImageCounter
{
	SDL_Surface *image;
	int counter;
};

class Image
{
public:
	Image(std::string filename);
	~Image();

	static void clearCache();

	SDL_Surface *getSurface();
	int getWidth();
	int getHeight();

protected:
private:
	static std::map<std::string, ImageCounter> images;

	std::string filename;
	SDL_Surface *image;
};

#endif // IMAGE_H
