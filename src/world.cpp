#include "world.h"

World::World(Application *application) // TODO: inform level
{
	this->application = application;
	screen = application->getScreen();
	event = application->getEvent();

	aircraft = new Aircraft(application);

	background1 = new Image(IMG_BACKGROUND1);
	background2 = new Image(IMG_BACKGROUND2);
	height1 = background1->getHeight();
	height2 = background2->getHeight();
	position1 = position2 = 0;

	event->addUpdater(this);
	screen->addDrawer(0, this);
}

World::~World()
{
	event->removeUpdater(this);
	screen->removeDrawer(0, this);

	delete aircraft;
	delete background1;
	delete background2;
}

void World::update()
{
	position1 += SPEED_BACKGROUND1;
	position2 += SPEED_BACKGROUND2;
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
