#include "enemy.h"

Enemy::Enemy(Application *application, int type)
{
	this->application = application;
	screen = application->getScreen();

	std::ostringstream filename;
	filename << IMG_ENEMY_PREFIX << type << IMG_ENEMY_SUFFIX;
	image = new Image(filename.str());

	width = image->getWidth();
	height = image->getHeight();
	left = 0;
	top = -height;

	// TODO: add it to enemy list

	application->addUpdater(this);
	screen->addDrawer(1, this);
}

Enemy::~Enemy()
{
	application->removeUpdater(this);
	screen->removeDrawer(1, this);

	delete image;

	// TODO: remove it from enemy list
}

void Enemy::update()
{
	top += ENEMY_SPEED;

	// TODO: detect colision?

	if (top > SCREEN_HEIGHT) {
		delete this;
	}
}

void Enemy::draw()
{
	screen->blitImage(left, top, image);
}
