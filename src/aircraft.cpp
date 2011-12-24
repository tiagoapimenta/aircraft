#include "aircraft.h"

Aircraft::Aircraft(Application *application)
{
	this->application = application;
	aircraft = new Image(IMG_AIRCRAFT);
	aircraft_left = new Image(IMG_AIRCRAFT_LEFT);
	aircraft_right = new Image(IMG_AIRCRAFT_RIGHT);
	width = aircraft->getWidth();
	height = aircraft->getHeight();
	left = (SCREEN_WIDTH - width) / 2;
	top = SCREEN_HEIGHT - height - 10;
	move_top = move_left = 0;
	application->getEvent()->addKeyEvent(this);
	current_aircraft = aircraft;
}

Aircraft::~Aircraft()
{
	application->getEvent()->removeKeyEvent(this);
	delete aircraft;
	delete aircraft_left;
	delete aircraft_right;
}

void Aircraft::update()
{
	left += move_left;
	top += move_top;
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
	else if (top > SCREEN_HEIGHT - height)
	{
		top = SCREEN_HEIGHT - height;
	}
}

void Aircraft::draw()
{
	application->getScreen()->blitImage(left, top, current_aircraft);
}

void Aircraft::keyDown(SDLKey key)
{
	switch (key) {
	case SDLK_UP:
		move_top = -1 * AIRCRAFT_SPEED;
		break;
	case SDLK_DOWN:
		move_top = 1 * AIRCRAFT_SPEED;
		break;
	case SDLK_LEFT:
		move_left = -1 * AIRCRAFT_SPEED;
		current_aircraft = aircraft_left;
		break;
	case SDLK_RIGHT:
		move_left = 1 * AIRCRAFT_SPEED;
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


