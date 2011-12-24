#ifndef WORLD_H
#define WORLD_H

#include "core.h"

#define SPEED_BACKGROUND1 1
#define SPEED_BACKGROUND2 2

class Application;
class Aircraft;

class World : public IDrawable, public IUpdatable
{
public:
	World(Application *application);
	~World();

	void update();
	void draw();

protected:
private:
	Application *application;
	Screen *screen;
	Event *event;
	Aircraft *aircraft;
	Image *background1, *background2;
	int height1;
	int height2;
	int position1;
	int position2;
};

#endif // WORLD_H
