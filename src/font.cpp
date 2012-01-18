#include "font.h"

std::map<int, FontCounter> Font::fonts;

Font::Font (int size, SDL_Color color)
{
	this->size = size;
	this->color = color;

	if (fonts.count (size) > 0)
	{
		std::map<int, FontCounter>::iterator it = fonts.find (size);
		it->second.counter++;
		font = it->second.font;
		return;
	}

	font = TTF_OpenFont (FONT_FILENAME, size);

	if (font == NULL) throw "Image not found.";

	TTF_SetFontStyle (font, TTF_STYLE_BOLD);

	FontCounter font_counter;
	font_counter.font = font;
	font_counter.counter = 1;
	fonts.insert (std::make_pair (size, font_counter));
}

Font::~Font()
{
	fonts.find (size)->second.counter--;
}

void Font::clearCache()
{
	for (std::map<int, FontCounter>::iterator it = fonts.begin(); it != fonts.end(); it++)
	{
		if (it->second.counter == 0)
		{
			TTF_CloseFont (it->second.font);
			fonts.erase (it); // TODO: Dangerous iterator usage. After erase the iterator is invalid so dereferencing it or comparing it with another iterator is invalid.
		}
	}
}

Image* Font::createText (std::string text)
{
	return new Image (TTF_RenderText_Solid (font, text.c_str(), color));
}
