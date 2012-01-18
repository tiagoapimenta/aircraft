#include "world.h"

World::World (Application *application, int level) // TODO: give level to open script?
{

	this->application = application;
	screen = application->getScreen();
	audio = application->getAudio();

	hud = new HUD (application);
	aircraft = new Aircraft (application, hud);

	std::ostringstream filename;
	filename << TXT_LEVEL_SCRIPT_PREFIX << level << TXT_LEVEL_SCRIPT_SUFFIX;
	this->level = new Level (filename.str());

	application->addUpdater (this);
	screen->addDrawer (BACKGROUND_LAYER, this);

	time = 0;
	do_time = false;

	nextStep();
}

World::~World()
{
	application->removeUpdater (this);
	screen->removeDrawer (BACKGROUND_LAYER, this);

	audio->stopMusic();

	Shot::deleteAll();
	Item::deleteAll();
	Enemy::deleteAll();
	Explosion::deleteAll();
	// TODO: Boss::deleteAll();

	clearBackground();

	delete level;
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
	if (do_time)
	{
		if (time > 0) time -= TIME_PER_FRAME;
		else
		{
			do_time = false;
			nextStep();
		}
	}

	for (std::vector<Background>::iterator it = backgrounds.begin() ; it != backgrounds.end(); it++)
	{
		it->position += it->speed;

		if (it->position > it->height) it->position = 0;
	}
}

void World::draw()
{
	for (std::vector<Background>::iterator it = backgrounds.begin() ; it != backgrounds.end(); it++)
	{
		screen->blitImage (0, it->position - it->height, it->image);

		if (it->position < SCREEN_HEIGHT) screen->blitImage (0, it->position, it->image);
	}
}

void World::nextStep()
{
	int done = false;
	while (!level->end() && !done)
	{
		Instruction instruction = level->nextInstruction();

		if (instruction.instruction.compare("background") == 0)
		{
			clearBackground();
			for (std::vector<Instruction>::iterator it = instruction.block.begin(); it != instruction.block.end(); it++)
			{
				if (it->instruction.compare("image") != 0) throw "Invalid instruction";
				addBackground(atoi(it->arguments.at(0).c_str()), atoi(it->arguments.at(1).c_str()));
			}
		}
		else if (instruction.instruction.compare("enemies") == 0)
		{
			for (std::vector<Instruction>::iterator it = instruction.block.begin(); it != instruction.block.end(); it++)
			{
				if (it->instruction.compare("enemy") != 0) throw "Invalid instruction";

				std::vector<int> properties;
				for (int i = 1; i < 7; i++)
				{
					properties.push_back(atoi(it->arguments.at(i).c_str()));
				}
				enemies.insert(std::make_pair(it->arguments.at(0), properties));
			}
		}
		else if (instruction.instruction.compare("music") == 0)
		{
			std::string prefix;
			if (instruction.arguments.at(0).compare("level") == 0) prefix = SND_MUSIC_LEVEL_PREFIX;
			else if (instruction.arguments.at(0).compare("boss") == 0) prefix = SND_MUSIC_BOSS_PREFIX;
			else throw "Invalid instruction";

			std::ostringstream filename;
			filename << prefix << atoi(instruction.arguments.at(1).c_str()) << SND_MUSIC_SUFFIX;

			audio->playMusic (filename.str());
		}
		else if (instruction.instruction.compare("delay") == 0)
		{
			do_time = true;
			time = atoi(instruction.arguments.at(0).c_str());
			done = true;
		}
		else if (instruction.instruction.compare("route") == 0)
		{
			for (std::vector<Instruction>::iterator it = instruction.block.begin(); it != instruction.block.end(); it++)
			{
				if (it->instruction.compare("raise") != 0) throw "Invalid instruction";

				if (enemies.count(it->arguments.at(0)) < 1) throw "Enemy not found";

				std::vector<int> arguments = enemies.find(it->arguments.at(0))->second;

				std::vector<EnemyMove> moves;

				for (std::vector<Instruction>::iterator it0 = it->block.begin(); it0 != it->block.end(); it0++)
				{
					EnemyMove move;
					move.shot = false;
					move.move_x = 0;
					move.move_y = 0;

					if (it0->instruction.compare("move") == 0)
					{
						move.move_x = atoi(it0->arguments.at(0).c_str());
						move.move_y = atoi(it0->arguments.at(1).c_str());
					}
					else if (it0->instruction.compare("shot") == 0)
					{
						move.shot = true; // TODO: shot number...
					}
					else throw "Invalid instruction";
					moves.push_back(move);
				}

				new Enemy(application, arguments.at(0), arguments.at(1), arguments.at(2) != 0, arguments.at(3), arguments.at(4), arguments.at(5), atoi(it->arguments.at(1).c_str()), atoi(it->arguments.at(2).c_str()), moves);
			}
			done = true;
		}
		else
		{
			throw "Invalid instruction";
		}
	}

	if (!done)
	{
		// TODO: you win
	}
}

void World::addBackground (int id, int speed)
{
	Background background;

	std::ostringstream filename;
	filename << IMG_BACKGROUND_PREFIX << id << IMG_BACKGROUND_SUFFIX;

	background.image = new Image (filename.str());
	background.speed = speed;
	background.position = 0;
	background.height = background.image->getHeight();

	backgrounds.push_back (background);
}

void World::clearBackground()
{
	for (std::vector<Background>::iterator it = backgrounds.begin() ; it != backgrounds.end(); it++)
	{
		delete it->image;
	}
	backgrounds.clear();
}
