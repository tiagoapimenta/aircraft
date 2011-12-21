#ifndef IMAGE_H
#define IMAGE_H

#include "core.h"

class Image
{
public:
	Image(std::string filename);
	~Image();
	SDL_Surface *getSurface();

protected:
private:
	SDL_Surface *image;
};

#endif // IMAGE_H
