#ifndef ITEM_H
#define ITEM_H

#include "core.h"

#define IMG_ITEM_LIFE "media/images/life.png"
#define IMG_ITEM_SPECIAL "media/images/special.png"

#define ITEM_LAYER 3
#define ITEM_SPEED 0.05f
#define ITEM_RADIUS 30
#define ITEM_DELAY 600

class Item : public IUpdatable, public IDrawable
{
public:
	Item(Application *application, int type, int left, int top);
	~Item();

	static void deleteAll();

	void update();
	void draw();

protected:
private:
	static std::set<Item*> itens;

	Application *application;
	Screen *screen;
	Aircraft *aircraft;
	Image *image;
	int time;
	int width;
	int height;
	int type;
	int left;
	int top;
	float rotation;
	int axis_x;
	int axis_y;
};

#endif // ITEM_H
