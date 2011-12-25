#include "shot.h"

std::set<Shot*> Shot::shots;

Shot::Shot(Application *application, int type, int left, int top, int move_left, int move_top, int damage, bool enemy)
{
	this->application = application;
	screen = application->getScreen();

	this->bomb = type == 3;
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

	shots.insert(this);

	application->addUpdater(this);
	screen->addDrawer(SHOT_LAYER, this);

	application->getAudio()->playSound((type == 1) ? SND_SHOT1 : SND_SHOT2);
}

Shot::~Shot()
{
	application->removeUpdater(this);
	screen->removeDrawer(SHOT_LAYER, this);

	for (int i = size; i--; )
	{
		delete image[i];
	}

	shots.erase(this);
}

void Shot::deleteAll()
{
	for (std::set<Shot*>::iterator it = shots.begin() ; it != shots.end(); it++ )
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
	if (bomb) new Explosion(application, BOMB_EXPLOSION, BOMB_DELAY, damage / 2, left - width / 2, top - height / 2);
	else new Explosion(application, SHOT_EXPLOSION, SHOT_DELAY, 0, left - width / 2, top - height / 2);
	delete this;
}
