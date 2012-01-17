#include "item.h"

std::set<Item*> Item::itens;

Item::Item(Application *application, int type, int left, int top)
{
	this->application = application;
	screen = application->getScreen();
	World *world = application->getWorld();
	aircraft = world->getAircraft();

	image = new Image(type == 1 ? IMG_ITEM_LIFE : IMG_ITEM_SPECIAL);

	width = image->getWidth();
	height = image->getHeight();

	this->type = type;
	axis_x = left - width / 2;
	axis_y = top - height / 2;
	rotation = 0;
	time = ITEM_DELAY;

	itens.insert(this);

	application->addUpdater(this);
	screen->addDrawer(ITEM_LAYER, this);
}

Item::~Item()
{
	application->removeUpdater(this);
	screen->removeDrawer(ITEM_LAYER, this);

	delete image;

	itens.erase(this);
}

void Item::deleteAll()
{
	for (std::set<Item*>::iterator it = itens.begin() ; it != itens.end(); it++ )
	{
		delete *it;
	}
}

void Item::update()
{
	left = cos(rotation) * ITEM_RADIUS + axis_x;
	top = sin(rotation) * ITEM_RADIUS + axis_y;

	rotation += ITEM_SPEED;
	if (rotation >= 2 * PI) rotation -= 2 * PI;

	if (aircraft->collide(left, top, width, height, true))
	{
		if (type == 1) aircraft->addLife();
		else aircraft->addBomb();
		delete this;
	}

	time--;
	if (time <= 0) delete this;
}

void Item::draw()
{
	screen->blitImage(left, top, image);
}
