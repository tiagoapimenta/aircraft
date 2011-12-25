#ifndef SHOT_H
#define SHOT_H

#include "core.h"

#define IMG_SHOT_PREFIX "media/images/shot"
#define IMG_SHOT_SEPARATOR "-"
#define IMG_SHOT_SUFFIX ".png"
#define SND_SHOT1 "media/audio/shot.ogg"
#define SND_SHOT2 "media/audio/laser.ogg"

#define MAX_SHOT 4
#define SHOT_ANIMATION 5
#define SHOT_LAYER 3

class Shot : public IDrawable, public IUpdatable
{
public:
	Shot(Application *application, int type, int left, int top, int move_left, int move_top, int damage, bool enemy);
	~Shot();

	static void addShot(Shot *shot);
	static void removeShot(Shot *shot);
	static void deleteAll();

	void update();
	void draw();
protected:
private:
	static std::set<Shot*> shots;

	Application *application;
	Screen *screen;
	Image *image[MAX_SHOT];
	Image *current_image;
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
