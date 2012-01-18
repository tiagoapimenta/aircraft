#include "aircraft.h"

Aircraft::Aircraft (Application *application, HUD *hud)
{
	this->application = application;
	screen = application->getScreen();
	event = application->getEvent();
	this->hud = hud;

	aircraft = new Image (IMG_AIRCRAFT);
	aircraft_left = new Image (IMG_AIRCRAFT_LEFT);
	aircraft_right = new Image (IMG_AIRCRAFT_RIGHT);
	fire1 = new Image (IMG_FIRE1);
	fire2 = new Image (IMG_FIRE2);

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
	bomb_interval = 0;
	bombing = false;
	animation = true;
	ghost_time = GHOST_TIME;
	energy = AIRCRAFT_LIFES;
	life = AIRCRAFT_CONTINUES;
	bomb = AIRCRAFT_BOMBS;
	explosion_time = 0;

	current_aircraft = aircraft;
	current_fire = fire1;
	used_move_left = 0;
	used_aircraft = aircraft;

	event->addKeyEvent (this);
	application->addUpdater (this);
	screen->addDrawer (AIRCRAFT_LAYER, this);
}

Aircraft::~Aircraft()
{
	event->removeKeyEvent (this);
	application->removeUpdater (this);
	screen->removeDrawer (AIRCRAFT_LAYER, this);

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
		if (top > SCREEN_HEIGHT - height - fire_height - FIRE_OFFSET_Y - AIRCRAFT_POSITION) top--;
		else animation = false;

		return;
	}

	if (explosion_time == 0)
	{
		left += move_left * AIRCRAFT_SPEED;
		top += move_top * AIRCRAFT_SPEED;
	}

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
	else if (shooting && shot_interval == 0 && explosion_time == 0)
	{
		new Shot (application, SHOT_TYPE, false, left + width / 2 + move_left * FIRE_OFFSET_X, top, 0, SHOT_SPEED, SHOT_DAMAGE, false);
		shot_interval = SHOT_INTERVAL;
	}

	if (bomb_interval > 0) bomb_interval--;
	else if (bombing && bomb_interval == 0 && bomb > 0 && explosion_time == 0)
	{
		new Shot (application, -BOMB_TYPE, true, left + width / 2 + move_left * FIRE_OFFSET_X, top, 0, BOMB_SPEED, BOMB_DAMAGE, false);
		bomb_interval = BOMB_INTERVAL;
		bomb--;
		hud->setBombs (bomb);
	}

	if (explosion_time > 0) explosion_time--;
	else if (ghost_time > 0) ghost_time--;

	used_aircraft = current_aircraft;
	used_move_left = move_left;
}

void Aircraft::draw()
{
	if (explosion_time || (ghost_time / GHOST_INTERVAL) % 2 == 1) return;

	screen->blitImage (left, top, used_aircraft);
	screen->blitImage (left + (width - fire_width) / 2 + used_move_left * FIRE_OFFSET_X, top + height + FIRE_OFFSET_Y, current_fire);
}

void Aircraft::keyDown (SDLKey key)
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
	case SDLK_LCTRL:
		shooting = true;
		break;
	case SDLK_SPACE:
		bombing = true;
		break;
	default:
		break;
	}
}

void Aircraft::keyUp (SDLKey key)
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
	case SDLK_LCTRL:
		shooting = false;
		break;
	case SDLK_SPACE:
		bombing = false;
		break;
	default:
		break;
	}
}

bool Aircraft::collide (int left, int top, int width, int height, bool item)
{
	return
		(item || energy > 0 && ghost_time == 0) && // TODO: do something to supress warnning
		left + width >= this->left &&
		top + height >= this->top &&
		left <= this->left + this->width &&
		top <= this->top + this->height;
}

void Aircraft::damage (int damage)
{
	if (ghost_time > 0) return;

	energy -= damage;

	if (energy <= 0) explode();
	else hud->setLifes (energy);
}

void Aircraft::explode()
{
	new Explosion (application, SHOT_EXPLOSION, SHOT_DELAY, 0, left + width / 2, top + height / 2);
	explosion_time = SHOT_DELAY;
	ghost_time = GHOST_TIME;

	energy = AIRCRAFT_LIFES;
	bomb = AIRCRAFT_BOMBS;
	life--;
	if (life == 0)
	{
		throw "Game Over"; // TODO: game over
	}

	hud->setLifes (energy);
	hud->setBombs (bomb);
	hud->setContinues (life);
}

void Aircraft::addLife()
{
	energy++;

	if (energy > AIRCRAFT_LIFES) energy = AIRCRAFT_LIFES;
	else application->getAudio()->playSound (SND_ITEM);

	hud->setLifes (energy);
}

void Aircraft::addBomb()
{
	bomb++;

	if (bomb > AIRCRAFT_BOMBS) bomb = AIRCRAFT_BOMBS;
	else application->getAudio()->playSound (SND_ITEM);

	hud->setBombs (bomb);
}

int Aircraft::bestGift()
{
	int max = 0;

	if (energy < AIRCRAFT_LIFES) max++;

	if (bomb < AIRCRAFT_BOMBS) max++;

	if (max == 0) return 0;

	if (max == 1) return (energy < AIRCRAFT_LIFES) ? 1 : 2;

	return rand() % 2 + 1;
}
