#include "world.h"

World::World(Application *application) // TODO: give level to open script?
{

	this->application = application;
	screen = application->getScreen();
	audio = application->getAudio();

	hud = new HUD(application);
	aircraft = new Aircraft(application, hud);

	addBackground(1, BACKGROUND_SPEED1);
	addBackground(2, BACKGROUND_SPEED2);

	application->addUpdater(this);
	screen->addDrawer(BACKGROUND_LAYER, this);

	audio->playMusic(SND_MUSIC_LEVEL1);
}

World::~World()
{
	application->removeUpdater(this);
	screen->removeDrawer(BACKGROUND_LAYER, this);

	audio->stopMusic();

	Shot::deleteAll();
	Item::deleteAll();
	Enemy::deleteAll();
	Explosion::deleteAll();
	// TODO: Boss::deleteAll();

	for (std::vector<Background>::iterator it = backgrounds.begin() ; it != backgrounds.end(); it++ )
	{
		delete it->image;
		backgrounds.erase(it); // TODO: Dangerous iterator usage. After erase the iterator is invalid so dereferencing it or comparing it with another iterator is invalid.
	}

	delete aircraft;
	delete hud;
}

Aircraft* World::getAircraft()
{
	return aircraft;
}

HUD* World::getHUD()
{
	return hud;
}

void World::update()
{
	for (std::vector<Background>::iterator it = backgrounds.begin() ; it != backgrounds.end(); it++ )
	{
		it->position += it->speed;
		if (it->position > it->height) it->position = 0;
	}
}

void World::draw()
{
	for (std::vector<Background>::iterator it = backgrounds.begin() ; it != backgrounds.end(); it++ )
	{
		screen->blitImage(0, it->position - it->height, it->image);
		if (it->position < SCREEN_HEIGHT) screen->blitImage(0, it->position, it->image);
	}
}

void World::nextStep()
{
	// TODO: next movement
}

void World::addBackground(int id, int speed)
{
	Background background;

	std::ostringstream filename;
	filename << IMG_BACKGROUND_PREFIX << id << IMG_BACKGROUND_SUFFIX;

	background.image = new Image(filename.str());
	background.speed = speed;
	background.position = 0;
	background.height = background.image->getHeight();

	backgrounds.push_back(background);
}
