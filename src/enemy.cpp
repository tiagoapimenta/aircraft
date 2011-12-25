#include "enemy.h"

std::vector<Enemy*> Enemy::enemies;

Enemy::Enemy(Application *application, int type, int life, int left, int top, int move)
{
	this->application = application;
	screen = application->getScreen();
	aircraft = application->getWorld()->getAircraft();



	std::ostringstream filename;
	filename << IMG_ENEMY_PREFIX << type << IMG_ENEMY_SUFFIX;
	image = new Image(filename.str());

	width = image->getWidth();
	height = image->getHeight();

	this->life = life;
	this->left = left + width / 2;
	this->top = top - height;
	this->move = move;

	addEnemy(this);

	application->addUpdater(this);
	screen->addDrawer(1, this);
}

Enemy::~Enemy()
{
	application->removeUpdater(this);
	screen->removeDrawer(1, this);

	delete image;

	removeEnemy(this);
}

void Enemy::addEnemy(Enemy *enemy)
{
	enemies.push_back(enemy);
}

void Enemy::removeEnemy(Enemy *enemy)
{
	for (std::vector<Enemy*>::iterator it = enemies.begin() ; it < enemies.end(); it++ )
	{
		if (*it == enemy)
		{
			enemies.erase(it);
			break;
		}
	}
}

void Enemy::deleteAll()
{
	for (std::vector<Enemy*>::iterator it = enemies.begin() ; it < enemies.end(); it++ )
	{
		delete *it;
	}
}

bool Enemy::checkShotCollision(int damage, int left, int top, int width, int height)
{
	bool collision = false;

	for (std::vector<Enemy*>::iterator it = enemies.begin() ; it < enemies.end(); it++ )
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

	if (life < 0) application->computePoints(damage + life);
	else application->computePoints(damage);

	if (life <= 0) delete this;
}

void Enemy::explode()
{
	// TODO: do explosion
	delete this;
}
