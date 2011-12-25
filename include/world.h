#ifndef WORLD_H
#define WORLD_H

#include "core.h"

#define IMG_BACKGROUND1 "media/images/background1.png"
#define IMG_BACKGROUND2 "media/images/background2.png"

#define SND_MUSIC_LEVEL1 "media/audio/level1.mid"

#define BACKGROUND_SPEED1 1
#define BACKGROUND_SPEED2 2
#define BACKGROUND_LAYER 0

class Application;
class Aircraft;
class HUD;

class World : public IDrawable, public IUpdatable
{
public:
	World(Application *application);
	~World();

	Aircraft* getAircraft();
	HUD* getHUD();
	void update();
	void draw();

protected:
private:
	Application *application;
	Screen *screen;
	Audio *audio;
	HUD *hud;
	Aircraft *aircraft;
	Image *background1, *background2;
	int height1;
	int height2;
	int position1;
	int position2;
};

#endif // WORLD_H
