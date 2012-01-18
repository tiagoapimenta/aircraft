#ifndef ENEMY_H
#define ENEMY_H

#include "core.h"

#define sign(n) ((n > 0) - (n < 0))

#define IMG_ENEMY_PREFIX "media/images/enemy"
#define IMG_ENEMY_SUFFIX ".png"

#define ENEMY_EXPLOSION 10
#define ENEMY_LAYER 1
#define ENEMY_POINTS 10
#define ENEMY_DROP 4
#define ENEMY_SHOT_SPEED 5

struct EnemyMove
{
	int move_x;
	int move_y;
	bool shot;
};

class Enemy : public IDrawable, public IUpdatable
{
public:
	Enemy (Application *application, int type, int shot, bool animated_shot, int damage, int life, int speed, int left, int top, std::vector<EnemyMove> moves);
	~Enemy();

	static int count();
	static void deleteAll();
	static bool checkCollisionDamage (int damage, int left, int top, int width, int height);

	void update();
	void draw();

	// TODO: void shoot();
	bool collide (int left, int top, int width, int height);
	void damage (int damage);
	void explode();
protected:
private:
	static std::set<Enemy*> enemies;

	Application *application;
	Screen *screen;
	World *world;
	Aircraft *aircraft;
	HUD *hud;
	Image *image;
	int shot;
	bool animated_shot;
	int shot_damage;
	int life;
	int speed;
	int left;
	int top;
	int width;
	int height;
	int last_top;
	int last_left;
	std::vector<EnemyMove> moves;
};

#endif // ENEMY_H
