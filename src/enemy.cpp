#include "enemy.h"

std::set<Enemy*> Enemy::enemies;

Enemy::Enemy(Application *application, int type, int life, int left, int top, int move)
{
	this->application = application;
	screen = application->getScreen();
	World *world = application->getWorld();
	aircraft = world->getAircraft();
	hud = world->getHUD();

	std::ostringstream filename;
	filename << IMG_ENEMY_PREFIX << type << IMG_ENEMY_SUFFIX;
	image = new Image(filename.str());

	width = image->getWidth();
	height = image->getHeight();

	this->life = life;
	this->left = left + width / 2;
	this->top = top - height;
	this->move = move;

	enemies.insert(this);

	application->addUpdater(this);
	screen->addDrawer(ENEMY_LAYER, this);
}

Enemy::~Enemy()
{
	application->removeUpdater(this);
	screen->removeDrawer(ENEMY_LAYER, this);

	delete image;

	enemies.erase(this);
}

void Enemy::deleteAll()
{
	for (std::set<Enemy*>::iterator it = enemies.begin() ; it != enemies.end(); it++ )
	{
		delete *it;
	}
}

bool Enemy::checkShotCollision(int damage, int left, int top, int width, int height)
{
	bool collision = false;

	for (std::set<Enemy*>::iterator it = enemies.begin() ; it != enemies.end(); it++ )
	{
		if ((*it)->collide(left, top, width, height))
		{
			(*it)->damage(damage);
			collision = true;
		}
	}

	return collision;
}

void Enemy::update()
{
	top += move * ENEMY_SPEED;

	if (aircraft->collide(left, top, width, height))
	{
		aircraft->damage(life * ENEMY_EXPLOSION);
		life = 0;
		explode();
	}

	if (top > SCREEN_HEIGHT) {
		delete this;
	}
}

void Enemy::draw()
{
	screen->blitImage(left, top, image);
}

bool Enemy::collide(int left, int top, int width, int height)
{
	return
	    life > 0 &&
	    left + width >= this->left &&
	    top + height >= this->top &&
	    left <= this->left + this->width &&
	    top <= this->top + this->height;
}

void Enemy::damage(int damage)
{
	life -= damage;

	if (life < 0) hud->computePoints((damage + life) * ENEMY_POINTS);
	else hud->computePoints(damage * ENEMY_POINTS);

	if (life <= 0) delete this;
}

void Enemy::explode()
{
	// TODO: do explosion
	delete this;
}
