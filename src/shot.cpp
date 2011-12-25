#include "shot.h"

Shot::Shot(Application *application, int type, int left, int top, int move_left, int move_top, bool enemy)
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
	this->enemy = enemy;
	index = 0;

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

	// TODO: colission

	if (top < 0 || top > SCREEN_HEIGHT + height || left < 0 || left > SCREEN_WIDTH + width) delete this;
}

void Shot::draw()
{
	screen->blitImage(left, top, current_image);
}