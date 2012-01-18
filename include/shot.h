#ifndef SHOT_H
#define SHOT_H

#include "core.h"

#define IMG_BOMB_PREFIX "media/images/bomb"
#define IMG_SHOT_PREFIX "media/images/shot"
#define IMG_SHOT_SEPARATOR "-"
#define IMG_SHOT_SUFFIX ".png"
#define SND_SHOT1 "media/audio/shot.ogg"
#define SND_SHOT2 "media/audio/laser.ogg"

#define MAX_SHOT 4
#define SHOT_ANIMATION 5
#define SHOT_LAYER 3
#define BOMB_DELAY 80
#define BOMB_EXPLOSION 2
#define BOMB_PADDING 100
#define SHOT_DELAY 40
#define SHOT_EXPLOSION 1


class Shot : public IDrawable, public IUpdatable
{
public:
	Shot (Application *application, int type, bool animation, int left, int top, int move_left, int move_top, int damage, bool enemy, bool play_sound = true);
	~Shot();

	static void deleteAll();

	void update();
	void draw();
protected:
private:
	static std::set<Shot*> shots;

	Application *application;
	Screen *screen;
	Aircraft *aircraft;
	Image *image[MAX_SHOT];
	Image *current_image;
	bool bomb;
	int left;
	int top;
	int width;
	int height;
	int move_top;
	int move_left;
	int index;
	int size;
	int damage;
	bool enemy;

	void explode();
};

#endif // SHOT_H
