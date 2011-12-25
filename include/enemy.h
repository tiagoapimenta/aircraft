#ifndef ENEMY_H
#define ENEMY_H

#include "core.h"

#define IMG_ENEMY_PREFIX "media/images/enemy"
#define IMG_ENEMY_SUFFIX ".png"

#define ENEMY_SPEED 1
#define ENEMY_EXPLOSION 10

class Enemy;

class Enemy : public IDrawable, public IUpdatable
{
public:
	Enemy(Application *application, int type, int life, int left, int top, int move);
	~Enemy();

	static void addEnemy(Enemy *enemy);
	static void removeEnemy(Enemy *enemy);
	static void deleteAll();
	static bool checkShotCollision(int damage, int left, int top, int width, int height);

	void update();
	void draw();
	bool collide(int left, int top, int width, int height);
	void damage(int damage);
protected:
private:
	static std::vector<Enemy*> enemies;

	Application *application;
	Screen *screen;
	Image *image;
	int left;
	int top;
	int move;
	int width;
	int height;
	int life;
};

#endif // ENEMY_H
