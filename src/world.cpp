#include "world.h"

World::World(Application *application) // TODO: give level to open script?
{

	this->application = application;
	screen = application->getScreen();

	aircraft = new Aircraft(application);

	background1 = new Image(IMG_BACKGROUND1);
	background2 = new Image(IMG_BACKGROUND2);
	height1 = background1->getHeight();
	height2 = background2->getHeight();
	position1 = position2 = 0;

	application->addUpdater(this);
	screen->addDrawer(BACKGROUND_LAYER, this);
}

World::~World()
{
	application->removeUpdater(this);
	screen->removeDrawer(BACKGROUND_LAYER, this);

	Shot::deleteAll();
	Enemy::deleteAll();
	//Boss::deleteAll();

	delete aircraft;
	delete background1;
	delete background2;
}

Aircraft* World::getAircraft()
{
	return aircraft;
}

void World::update()
{
	position1 += BACKGROUND_SPEED1;
	position2 += BACKGROUND_SPEED2;
	if (position1 > height1) position1 = 0;
	if (position2 > height2) position2 = 0;
}

void World::draw()
{
	screen->blitImage(0, position1 - height1, background1);
	if (position1 < SCREEN_HEIGHT) screen->blitImage(0, position1, background1);
	screen->blitImage(0, position2 - height2, background2);
	if (position2 < SCREEN_HEIGHT) screen->blitImage(0, position2, background2);
}
