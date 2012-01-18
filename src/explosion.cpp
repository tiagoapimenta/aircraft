#include "explosion.h"

std::set<Explosion*> Explosion::explosions;

Explosion::Explosion (Application *application, int type, int delay, int damage, int left, int top, bool play_sound)
{
	this->application = application;
	screen = application->getScreen();

	std::ostringstream filename;
	filename << IMG_EXPLOSION_PREFIX << type << IMG_EXPLOSION_SUFFIX;
	image = new Image (filename.str());

	width = image->getWidth();
	height = image->getHeight();

	this->left = left - width / 2;
	this->top = top - height / 2;
	time = delay;

	explosions.insert (this);

	application->addUpdater (this);
	screen->addDrawer (EXPLOSION_LAYER, this);

	if (play_sound) application->getAudio()->playSound (SND_EXPLOSION);

	this->damage = damage;
}

Explosion::~Explosion()
{
	application->removeUpdater (this);
	screen->removeDrawer (EXPLOSION_LAYER, this);

	delete image;

	explosions.erase (this);
}

void Explosion::deleteAll()
{
	for (std::set<Explosion*>::iterator it = explosions.begin() ; it != explosions.end(); it++)
	{
		delete *it; // TODO: Dangerous iterator usage. After erase the iterator is invalid so dereferencing it or comparing it with another iterator is invalid.
	}
}

void Explosion::update()
{
	if (damage)
	{
		Enemy::checkCollisionDamage (damage, this->left, this->top, width, height); // TODO: do not hit same enemy several times
	}

	time--;

	if (time <= 0) delete this;
}

void Explosion::draw()
{
	screen->blitImage (left, top, image);
}
