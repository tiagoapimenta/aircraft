#ifndef CORE_H
#define CORE_H

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

#include "interfaces.h" // It must comes first, I don't know wky it doesn't works if it isn't, even with "class Name;" prototype.

#include "application.h"
#include "image.h"
#include "font.h"
#include "screen.h"
#include "audio.h"
#include "event.h"
#include "world.h"
#include "hud.h"
#include "aircraft.h"
#include "enemy.h"
#include "shot.h"
#include "explosion.h"
#include "item.h"
#include "level.h"
// TODO: boss

#endif
