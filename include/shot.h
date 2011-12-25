#ifndef SHOT_H
#define SHOT_H

#include "core.h"

#define MAX_SHOT 4

class Shot : public IDrawable, public IUpdatable
{
	public:
		Shot(Application *application, int type, int top, int left, int move_top, int move_left, bool enemy);
		~Shot();

		void update();
		void draw();
	protected:
	private:
		Application *application;
		Screen *screen;
		Event *event;
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
		bool enemy;
};

#endif // SHOT_H
