#ifndef WORLD_H
#define WORLD_H

#include "core.h"

#define IMG_BACKGROUND_PREFIX "media/images/background"
#define IMG_BACKGROUND_SUFFIX ".png"

#define SND_MUSIC_LEVEL_PREFIX "media/audio/level"
#define SND_MUSIC_BOSS_PREFIX "media/audio/level"
#define SND_MUSIC_SUFFIX ".mid"

#define TXT_LEVEL_SCRIPT_PREFIX "media/levels/level"
#define TXT_LEVEL_SCRIPT_SUFFIX ".script"

#define BACKGROUND_LAYER 0

class Application;
class Aircraft;
class HUD;
class Level;

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
	World (Application *application, int level);
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
	Level *level;
	std::vector<Background> backgrounds;
	int time;
	bool do_time;
	std::map<std::string, std::vector<int> > enemies;

	void addBackground (int id, int speed);
	void clearBackground();
};

#endif // WORLD_H
