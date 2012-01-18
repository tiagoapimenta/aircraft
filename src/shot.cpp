#include "shot.h"

std::set<Shot*> Shot::shots;

Shot::Shot (Application *application, int type, bool animation, int left, int top, int move_left, int move_top, int damage, bool enemy, bool play_sound)
{
	this->application = application;
	screen = application->getScreen();
	World *world = application->getWorld();
	aircraft = world->getAircraft();

	std::string preffix = IMG_SHOT_PREFIX;

	if (type < 0)
	{
		bomb = true;
		type *= -1;
		preffix = IMG_BOMB_PREFIX;
	}
	else bomb = false;

	std::ostringstream filename;

	if (animation)
	{
		size = 4;

		for (int i = size; i--;)
		{
			filename.str ("");
			filename << preffix << type << IMG_SHOT_SEPARATOR << i + 1 << IMG_SHOT_SUFFIX;
			image[i] = new Image (filename.str());
		}
	}
	else
	{
		size = 1;
		filename << preffix << type << IMG_SHOT_SUFFIX;
		image[0] = new Image (filename.str());
	}

	current_image = image[0];

	width = current_image->getWidth();
	height = current_image->getHeight();

	this->left = left - width / 2;
	this->top = top - height / 2;
	this->move_left = move_left;
	this->move_top = move_top;
	this->damage = damage;
	this->enemy = enemy;
	index = 0;

	shots.insert (this);

	application->addUpdater (this);
	screen->addDrawer (SHOT_LAYER, this);

	if (play_sound) application->getAudio()->playSound ( (type == 1) ? SND_SHOT1 : SND_SHOT2);
}

Shot::~Shot()
{
	application->removeUpdater (this);
	screen->removeDrawer (SHOT_LAYER, this);

	for (int i = size; i--;)
	{
		delete image[i];
	}

	shots.erase (this);
}

void Shot::deleteAll()
{
	std::set<Shot*> trash;

	for (std::set<Shot*>::iterator it = shots.begin() ; it != shots.end(); it++)
	{
		trash.insert(*it);
	}

	for (std::set<Shot*>::iterator it = trash.begin() ; it != trash.end(); it++)
	{
		delete *it;
	}
	trash.clear();
}

void Shot::update()
{
	top += move_top;
	left += move_left;

	if (size > 1) {
		index++;

		if (index > size * SHOT_ANIMATION) index = 0;

		current_image = image[index / SHOT_ANIMATION];
	}

	if (enemy)
	{
		if (aircraft->collide (left, top, width, height))
		{
			aircraft->damage (damage);
			explode();
			return;
		}
	}
	else
	{
		if (Enemy::checkCollisionDamage (damage, left, top, width, height)) // TODO: do it with boss too
		{
			explode();
			return;
		}
	}

	if (bomb && top < BOMB_PADDING)
	{
		explode();
		return;
	}

	if (top < 0 || top > SCREEN_HEIGHT + height || left < 0 || left > SCREEN_WIDTH + width) delete this;
}

void Shot::draw()
{
	screen->blitImage (left, top, current_image);
}

void Shot::explode()
{
	if (bomb) new Explosion (application, BOMB_EXPLOSION, BOMB_DELAY, damage / 2, left - width / 2, top - height / 2);

	delete this;
}
