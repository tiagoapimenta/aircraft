#include "aircraft.h"

Aircraft::Aircraft(Application *application)
{
	this->application = application;
	screen = application->getScreen();
	event = application->getEvent();

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
	top = SCREEN_HEIGHT;
	move_top = move_left = 0;
	fire_index = 0;
	shot_interval = 0;
	shooting = false;
	animation = true;
	immortal_time = IMMORTAL_TIME;
	energy = AIRCRAFT_LIFES;
	life = AIRCRAFT_CONTINUES;

	current_aircraft = aircraft;
	current_fire = fire1;

	event->addKeyEvent(this);
	application->addUpdater(this);
	screen->addDrawer(1, this);
}

Aircraft::~Aircraft()
{
	event->removeKeyEvent(this);
	application->removeUpdater(this);
	screen->removeDrawer(1, this);

	delete aircraft;
	delete aircraft_left;
	delete aircraft_right;
	delete fire1;
	delete fire2;
}

void Aircraft::update()
{
	if (animation)
	{
		if (top > SCREEN_HEIGHT - height -fire_height - FIRE_OFFSET_Y - AIRCRAFT_POSITION) top--;
		else animation = false;
		return;
	}

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
	else if (top > SCREEN_HEIGHT - height - fire_height + FIRE_OFFSET_Y)
	{
		top = SCREEN_HEIGHT - height - fire_height + FIRE_OFFSET_Y;
	}

	current_fire = (fire_index / FIRE_LOOP == 0) ? fire1 : fire2;
	fire_index++;
	if (fire_index >= 2 * FIRE_LOOP) fire_index = 0;

	if (shot_interval > 0) shot_interval--;
	else if (shooting && shot_interval == 0) {
		new Shot(application, SHOT_TYPE, left + width / 2 + move_left * FIRE_OFFSET_X, top, 0, SHOT_SPEED, SHOT_DAMAGE, false);
		shot_interval = SHOT_INTERVAL;
	}

	if (immortal_time > 0) immortal_time--;

	// TODO: special bomb
}

void Aircraft::draw()
{
	if ((immortal_time / IMMORTAL_INTERVAL) % 2 == 1) return;

	screen->blitImage(left, top, current_aircraft);
	screen->blitImage(left + (width - fire_width) / 2 + move_left * FIRE_OFFSET_X, top + height + FIRE_OFFSET_Y, current_fire);
}

void Aircraft::keyDown(SDLKey key)
{
	if (animation) return;

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
	case SDLK_LCTRL:
		shooting = true;
		break;
	default:
		break;
	}
}

void Aircraft::keyUp(SDLKey key)
{
	if (animation) return;

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
	case SDLK_LCTRL:
		shooting = false;
		break;
	default:
		break;
	}
}

bool Aircraft::collide(int left, int top, int width, int height)
{
	return
		energy > 0 && immortal_time == 0 &&
	    left + width >= this->left &&
	    top + height >= this->top &&
	    left <= this->left + this->width &&
	    top <= this->top + this->height;
}

void Aircraft::damage(int damage)
{
	if (immortal_time > 0) return;

	energy -= damage;

	if (energy <= 0) explode();
}

void Aircraft::explode()
{
	// TODO: do the explosion, but do not delete this
	energy = AIRCRAFT_LIFES;
	life--;
	immortal_time = IMMORTAL_TIME;
	// TODO: game over if life == 0
}
