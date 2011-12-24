#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "core.h"

#define AIRCRAFT_SPEED 2

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
	Image *aircraft, *aircraft_left, *aircraft_right, *current_aircraft;
	int width;
	int height;
	int left;
	int top;
	int move_top;
	int move_left;
};

#endif // AIRCRAFT_H
