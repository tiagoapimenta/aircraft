#ifndef FONT_H
#define FONT_H

#include "core.h"

#define FONT_FILENAME "media/fonts/helvetica.ttf"

struct FontCounter
{
	TTF_Font *font;
	int counter;
};

class Image;

class Font
{
public:
	Font(int size, SDL_Color color);
	~Font();

	static void clearCache();

	Image* createText(std::string text);
protected:
private:
	static std::map<int, FontCounter> fonts;

	int size;
	TTF_Font *font;
	SDL_Color color;
};

#endif // FONT_H
