#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "core.h"

#define AIRCRAFT_SPEED 4
#define FIRE_LOOP 5
#define FIRE_OFFSET 2

class Application;

class Aircraft : public IKeyEventHandleable, public IUpdatable, public IDrawable
{
public:
	Aircraft(Application* application);
	~Aircraft();

	void update();
	void draw();
	void keyDown(SDLKey key);
	void keyUp(SDLKey key);

protected:
private:
	Application* application;
	Screen* screen;
	Event* event;
	Image *aircraft, *aircraft_left, *aircraft_right, *current_aircraft;
	Image *fire1, *fire2, *current_fire;
	int width;
	int height;
	int fire_width;
	int fire_height;
	int fire_index;
	int left;
	int top;
	int move_top;
	int move_left;
};

#endif // AIRCRAFT_H
