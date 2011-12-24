#include "aircraft.h"

Aircraft::Aircraft(Application *application)
{
	this->application = application;
	aircraft = new Image(IMG_AIRCRAFT);
	aircraft_left = new Image(IMG_AIRCRAFT_LEFT);
	aircraft_right = new Image(IMG_AIRCRAFT_RIGHT);
	fire1 = new Image(IMG_FIRE1);
	fire2 = new Image(IMG_FIRE2);
	width = aircraft->getWidth();
	height = aircraft->getHeight();
	fire_width = fire1->getWidth();
	fire_height = fire1->getHeight();
	left = (SCREEN_WIDTH - width) / 2;
	top = SCREEN_HEIGHT - height - fire_height - 10;
	move_top = move_left = 0;
	application->getEvent()->addKeyEvent(this);
	current_aircraft = aircraft;
	current_fire = fire1;
	fire_index = 0;
}

Aircraft::~Aircraft()
{
	application->getEvent()->removeKeyEvent(this);
	delete aircraft;
	delete aircraft_left;
	delete aircraft_right;
	delete fire1;
	delete fire2;
}

void Aircraft::update()
{
	left += move_left * AIRCRAFT_SPEED;
	top += move_top * AIRCRAFT_SPEED;
	if (left < 0)
	{
		left = 0;
	}
	else if (left > SCREEN_WIDTH - width)
	{
		left = SCREEN_WIDTH - width;
	}
	if (top < 0)
	{
		top = 0;
	}
	else if (top > SCREEN_HEIGHT - height - fire_height)
	{
		top = SCREEN_HEIGHT - height - fire_height;
	}
	current_fire = (fire_index / FIRE_LOOP == 0) ? fire1 : fire2;
	fire_index++;
	if (fire_index >= 2 * FIRE_LOOP) fire_index = 0;
}

void Aircraft::draw()
{
	application->getScreen()->blitImage(left, top, current_aircraft);
	application->getScreen()->blitImage(left + (width - fire_width) / 2 + move_left * FIRE_OFFSET, top + height, current_fire);
}

void Aircraft::keyDown(SDLKey key)
{
	switch (key) {
	case SDLK_UP:
		move_top = -1;
		break;
	case SDLK_DOWN:
		move_top = 1;
		break;
	case SDLK_LEFT:
		move_left = -1;
		current_aircraft = aircraft_left;
		break;
	case SDLK_RIGHT:
		move_left = 1;
		current_aircraft = aircraft_right;
		break;
	default:
		break;
	}
}

void Aircraft::keyUp(SDLKey key)
{
	switch (key) {
	case SDLK_UP:
		if (move_top < 0) move_top = 0;
		break;
	case SDLK_DOWN:
		if (move_top > 0) move_top = 0;
		break;
	case SDLK_LEFT:
		if (move_left < 0)
		{
			move_left = 0;
			current_aircraft = aircraft;
		}
		break;
	case SDLK_RIGHT:
		if (move_left > 0)
		{
			move_left = 0;
			current_aircraft = aircraft;
		}
		break;
	default:
		break;
	}
}


