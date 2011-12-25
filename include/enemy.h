#ifndef ENEMY_H
#define ENEMY_H

#include "core.h"

#define IMG_ENEMY_PREFIX "media/images/enemy"
#define IMG_ENEMY_SUFFIX ".png"

#define ENEMY_SPEED 1

class Enemy : public IDrawable, public IUpdatable
{
	public:
		Enemy(Application *application, int type);
		~Enemy();

		void update();
		void draw();
	protected:
	private:
		Application *application;
		Screen *screen;
		Image *image;
		int left;
		int top;
		int width;
		int height;
};

#endif // ENEMY_H
