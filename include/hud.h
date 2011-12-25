#ifndef HUD_H
#define HUD_H

#include "core.h"

#define HUD_LAYER 4

#define HUD_MARGIN_LEFT 10
#define HUD_MARGIN_TOP 10
#define HUD_MARGIN_RIGTH 10
#define HUD_MARGIN_BOTTOM 10
#define HUD_MARGIN_SPAN 5

#define IMG_LIFE "media/images/life.png"
#define IMG_BOMB "media/images/special.png"
#define IMG_CONTINUE "media/images/continue.png"

class Font;

class HUD : public IDrawable
{
public:
	HUD(Application *application);
	~HUD();

	void draw();

	void computePoints(int points);

	void setLifes(int lifes);
	void setContinues(int continues);
	void setBombs(int bombs);
protected:
private:
	Application *application;
	Screen *screen;
	Font *font;
	Image *img_life;
	Image *img_bomb;
	Image *img_continue;
	Image *img_points;
	int lifes;
	int bombs;
	int continues;
	int points;
	int img_life_width;
	int img_life_height;
	int img_bomb_width;
	int img_bomb_height;
	int img_continue_width;
	int img_continue_height;
};

#endif // HUD_H
