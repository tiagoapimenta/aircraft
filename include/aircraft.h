#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "core.h"

#define IMG_AIRCRAFT "media/images/aircraft.png"
#define IMG_AIRCRAFT_RIGHT "media/images/aircraft-right.png"
#define IMG_AIRCRAFT_LEFT "media/images/aircraft-left.png"

#define IMG_FIRE1 "media/images/fire1.png"
#define IMG_FIRE2 "media/images/fire2.png"

#define AIRCRAFT_SPEED 4
#define AIRCRAFT_LIFES 5
#define AIRCRAFT_CONTINUES 3
#define AIRCRAFT_POSITION 10
#define FIRE_LOOP 5
#define FIRE_OFFSET_X 2
#define FIRE_OFFSET_Y -1
#define SHOT_INTERVAL 7
#define SHOT_TYPE 1
#define SHOT_SPEED -5
#define SHOT_DAMAGE 1
#define IMMORTAL_TIME 120
#define IMMORTAL_INTERVAL 5

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

	bool collide(int left, int top, int width, int height);
	void damage(int damage);
	void explode();

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
	bool shooting;
	int shot_interval;
	int life;
	int energy;
	int immortal_time;
	bool animation;
};

#endif // AIRCRAFT_H
