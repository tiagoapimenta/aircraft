#ifndef WORLD_H
#define WORLD_H

#include "core.h"

#define IMG_BACKGROUND_PREFIX "media/images/background"
#define IMG_BACKGROUND_SUFFIX ".png"

#define SND_MUSIC_LEVEL1 "media/audio/level1.mid"

#define BACKGROUND_SPEED1 1
#define BACKGROUND_SPEED2 2
#define BACKGROUND_LAYER 0

class Application;
class Aircraft;
class HUD;

struct Background
{
	Image *image;
	int speed;
	int height;
	int position;
};

class World : public IDrawable, public IUpdatable
{
public:
	World(Application *application);
	~World();

	Aircraft* getAircraft();
	HUD* getHUD();
	void update();
	void draw();

	void nextStep();

protected:
private:
	Application *application;
	Screen *screen;
	Audio *audio;
	HUD *hud;
	Aircraft *aircraft;
	std::vector<Background> backgrounds;

	void addBackground(int id, int speed);
};

#endif // WORLD_H
