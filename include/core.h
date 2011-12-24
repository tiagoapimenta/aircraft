#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "interfaces.h" // It must comes first, I don't know wky it doesn't works if it isn't, even with "class Name;" prototype.

#include "application.h"
#include "image.h"
#include "screen.h"
#include "event.h"
#include "world.h"
#include "aircraft.h"
//enemy
//fire
//boss

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_BPP 32
#define FRAMES_PER_SECOND 40
#define TIME_PER_FRAME (1000 / FRAMES_PER_SECOND)

#define SCREEN_TITLE "Aircraft Burner"

#define IMG_AIRCRAFT "media/images/aircraft.png"
#define IMG_AIRCRAFT_RIGHT "media/images/aircraft-right.png"
#define IMG_AIRCRAFT_LEFT "media/images/aircraft-left.png"

#define IMG_FIRE1 "media/images/fire1.png"
#define IMG_FIRE2 "media/images/fire2.png"

#define IMG_BACKGROUND1 "media/images/background1.png"
#define IMG_BACKGROUND2 "media/images/background2.png"

#endif
