#include "explosion.h"

std::set<Explosion*> Explosion::explosions;

Explosion::Explosion(Application *application, int type, int delay, int damage, int left, int top)
{
	this->application = application;
	screen = application->getScreen();

	std::ostringstream filename;
	filename << IMG_EXPLOSION_PREFIX << type << IMG_EXPLOSION_SUFFIX;
	image = new Image(filename.str());

	int width = image->getWidth();
	int height = image->getHeight();

	this->left = left - width / 2;
	this->top = top - height / 2;
	time = delay;

	explosions.insert(this);

	application->addUpdater(this);
	screen->addDrawer(EXPLOSION_LAYER, this);

	application->getAudio()->playSound(SND_EXPLOSION);

	if (damage)
	{
		// TODO: Apply more damage to enemies
	}
}

Explosion::~Explosion()
{
	application->removeUpdater(this);
	screen->removeDrawer(EXPLOSION_LAYER, this);

	delete image;

	explosions.erase(this);
}

void Explosion::deleteAll()
{
	for (std::set<Explosion*>::iterator it = explosions.begin() ; it != explosions.end(); it++ )
	{
		delete *it;
	}
}

void Explosion::update()
{
	time--;
	if (time <= 0) delete this;
}

void Explosion::draw()
{
	screen->blitImage(left, top, image);
}
