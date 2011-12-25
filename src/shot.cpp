#include "shot.h"

std::vector<Shot*> Shot::shots;

Shot::Shot(Application *application, int type, int left, int top, int move_left, int move_top, int damage, bool enemy)
{
	this->application = application;
	screen = application->getScreen();

	std::ostringstream filename;
	if (type == 3)
	{
		size = 4;
		for (int i = size; i--; )
		{
			filename.str("");
			filename << IMG_SHOT_PREFIX << type << IMG_SHOT_SEPARATOR << i + 1 << IMG_SHOT_SUFFIX;
			image[i] = new Image(filename.str());
		}
	}
	else
	{
		size = 1;
		filename << IMG_SHOT_PREFIX << type << IMG_SHOT_SUFFIX;
		image[0] = new Image(filename.str());
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

	addShot(this);

	application->addUpdater(this);
	screen->addDrawer(2, this);
}

Shot::~Shot()
{
	application->removeUpdater(this);
	screen->removeDrawer(2, this);

	for (int i = size; i--; )
	{
		delete image[i];
	}

	removeShot(this);
}

void Shot::addShot(Shot *shot)
{
	shots.push_back(shot);
}

void Shot::removeShot(Shot *shot)
{
	for (std::vector<Shot*>::iterator it = shots.begin() ; it < shots.end(); it++ )
	{
		if (*it == shot)
		{
			shots.erase(it);
			break;
		}
	}
}

void Shot::deleteAll()
{
	for (std::vector<Shot*>::iterator it = shots.begin() ; it < shots.end(); it++ )
	{
		delete *it;
	}
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
		// TODO: check hero collision
	}
	else
	{
		if (Enemy::checkShotCollision(damage, left, top, width, height)) // TODO: do it with boss too
		{
			explode();
			return;
		}
	}

	if (top < 0 || top > SCREEN_HEIGHT + height || left < 0 || left > SCREEN_WIDTH + width) delete this;
}

void Shot::draw()
{
	screen->blitImage(left, top, current_image);
}

void Shot::explode()
{
	// TODO: do explosion, if damage > 1 then explosion bigger, and give damage again, 50% of damage
}
