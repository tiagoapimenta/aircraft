#include "enemy.h"

std::set<Enemy*> Enemy::enemies;

Enemy::Enemy (Application *application, int type, int shot, bool animated_shot, int damage, int life, int speed, int left, int top, std::vector<EnemyMove> moves)
{
	this->application = application;
	screen = application->getScreen();
	world = application->getWorld();
	aircraft = world->getAircraft();
	hud = world->getHUD();

	std::ostringstream filename;
	filename << IMG_ENEMY_PREFIX << type << IMG_ENEMY_SUFFIX;
	image = new Image (filename.str());

	width = image->getWidth();
	height = image->getHeight();

	this->shot = shot;
	this->animated_shot = animated_shot;
	this->shot_damage = damage;
	this->life = life;
	this->speed = speed;
	this->left = last_left = left - width / 2;
	this->top = last_top = top - height;
	this->moves = moves;

	enemies.insert (this);

	application->addUpdater (this);
	screen->addDrawer (ENEMY_LAYER, this);
}

Enemy::~Enemy()
{
	application->removeUpdater (this);
	screen->removeDrawer (ENEMY_LAYER, this);

	delete image;

	enemies.erase (this);

	if (enemies.empty()) world->nextStep();
}

int Enemy::count()
{
	return enemies.size();
}

void Enemy::deleteAll()
{
	std::set<Enemy*> trash;

	for (std::set<Enemy*>::iterator it = enemies.begin() ; it != enemies.end(); it++)
	{
		trash.insert(*it);
	}

	for (std::set<Enemy*>::iterator it = trash.begin() ; it != trash.end(); it++)
	{
		delete *it;
	}
	trash.clear();
}

bool Enemy::checkCollisionDamage (int damage, int left, int top, int width, int height)
{
	bool collision = false;

	for (std::set<Enemy*>::iterator it = enemies.begin() ; it != enemies.end(); it++)
	{
		if ( (*it)->collide (left, top, width, height))
		{
			(*it)->damage (damage);
			collision = true;
		}
	}

	return collision;
}

void Enemy::update()
{
	EnemyMove move = moves.front();

	bool done = false;

	if (move.shot)
	{
		shoot(1);
		done = true;
		// TODO: Should it skip the movement?
	}
	else
	{
		int target_x = move.move_x - width / 2;
		int target_y = move.move_y - height;
		int move_x = sign (target_x - left);
		int move_y = sign (target_y - top);

		if (abs (move_x) > abs (move_y))
		{
			move_x *= speed;
			left += move_x;
			top = last_top + (target_y - last_top) * (left - last_left) / (target_x - last_left);

			if ((move_x > 0 && left >= target_x) || (move_x < 0 && left <= target_x)) done = true;
		}
		else
		{
			move_y *= speed;
			top += move_y;
			left = last_left + (target_x - last_left) * (top - last_top) / (target_y - last_top);

			if ((move_y > 0 && top >= target_y) || (move_y < 0 && top <= target_y)) done = true;
		}
	}

	if (done)
	{
		moves.erase (moves.begin());
		last_left = left;
		last_top = top;
	}

	if (moves.empty()) {
		delete this;
	}

	if (aircraft->collide (left, top, width, height))
	{
		aircraft->damage (life * ENEMY_EXPLOSION);
		life = 0;
		explode();
	}
}

void Enemy::draw()
{
	screen->blitImage (left, top, image);
}

bool Enemy::collide (int left, int top, int width, int height)
{
	return
		life > 0 &&
		left + width >= this->left &&
		top + height >= this->top &&
		left <= this->left + this->width &&
		top <= this->top + this->height;
}

void Enemy::damage (int damage)
{
	life -= damage;

	if (life < 0) hud->computePoints ( (damage + life) * ENEMY_POINTS);
	else hud->computePoints (damage * ENEMY_POINTS);

	if (life <= 0) explode();
}

void Enemy::explode()
{
	new Explosion (application, SHOT_EXPLOSION, SHOT_DELAY, 0, left + width / 2, top + height / 2);

	if (rand() % ENEMY_DROP == 0)
	{
		int type = aircraft->bestGift();

		if (type != 0) new Item (application, type, left + width / 2, top + height / 2);
	}

	delete this;
}

void Enemy::shoot(int count)
{
	// TODO: multi-shot
	new Shot (application, shot, animated_shot, left + width / 2, top + height, 0, ENEMY_SHOT_SPEED, shot_damage, true);
}
