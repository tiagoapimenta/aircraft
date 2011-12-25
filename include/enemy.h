#ifndef ENEMY_H
#define ENEMY_H

#include "core.h"

#define ENEMY_SPEED 1;

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
		Event *event;
		Image *image;
		int left;
		int top;
		int width;
		int height;
};

#endif // ENEMY_H
