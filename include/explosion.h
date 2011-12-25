#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "core.h"

#define IMG_EXPLOSION_PREFIX "media/images/explosion"
#define IMG_EXPLOSION_SUFFIX ".png"

#define SND_EXPLOSION "media/audio/explosion.ogg"

#define EXPLOSION_LAYER 4

class Explosion : public IDrawable, public IUpdatable
{
public:
	Explosion(Application *application, int type, int delay, int damage, int left, int top, bool play_sound = true);
	~Explosion();

	static void deleteAll();

	void update();
	void draw();

protected:
private:
	static std::set<Explosion*> explosions;

	Application *application;
	Screen *screen;
	int left;
	int top;
	int time;

	Image *image;
};

#endif // EXPLOSION_H
