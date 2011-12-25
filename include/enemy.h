#ifndef ENEMY_H
#define ENEMY_H

#include "core.h"

#define IMG_ENEMY_PREFIX "media/images/enemy"
#define IMG_ENEMY_SUFFIX ".png"

#define ENEMY_SPEED 1
#define ENEMY_EXPLOSION 10
#define ENEMY_LAYER 1
#define ENEMY_POINTS 10

class Enemy : public IDrawable, public IUpdatable
{
public:
	Enemy(Application *application, int type, int life, int left, int top, int move);
	~Enemy();

	static void deleteAll();
	static bool checkShotCollision(int damage, int left, int top, int width, int height);

	void update();
	void draw();

	//void shoot();
	bool collide(int left, int top, int width, int height);
	void damage(int damage);
	void explode();
protected:
private:
	static std::set<Enemy*> enemies;

	Application *application;
	Screen *screen;
	Aircraft *aircraft;
	HUD *hud;
	Image *image;
	int left;
	int top;
	int move;
	int width;
	int height;
	int life;
};

#endif // ENEMY_H
