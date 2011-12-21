#ifndef MAIN_H
#define MAIN_H

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define FRAMES_PER_SECOND 40

#define SCREEN_TITLE "Aircraft Burner"

#define IMG_NAVE "media/images/nave1.png"

SDL_Surface *load_image(const char* filename);

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *target);

#endif
