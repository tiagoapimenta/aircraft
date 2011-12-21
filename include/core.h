#ifndef CORE_H
#define CORE_H

#include <string>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "image.h"
#include "screen.h"
#include "util.h"
#include "event.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define FRAMES_PER_SECOND 40
#define TIME_PER_FRAME (1000 / FRAMES_PER_SECOND)

#define SCREEN_TITLE "Aircraft Burner"

#define IMG_NAVE "media/images/nave1.png"

#endif
