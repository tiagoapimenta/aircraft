#include "hud.h"

HUD::HUD(Application *application)
{
	this->application = application;
	screen = application->getScreen();
	event = application->getEvent();

	SDL_Color black = {0, 0, 128};
	font = new Font(24, black);

	img_life = new Image(IMG_LIFE);
	img_bomb = new Image(IMG_BOMB);
	img_continue = new Image(IMG_CONTINUE);

	img_life_width = img_life->getWidth();
	img_life_height = img_life->getHeight();
	img_bomb_width = img_bomb->getWidth();
	img_bomb_height = img_bomb->getHeight();
	img_continue_width = img_continue->getWidth();
	img_continue_height = img_continue->getHeight();

	lifes = AIRCRAFT_LIFES;
	continues = AIRCRAFT_CONTINUES;
	bombs = AIRCRAFT_BOMBS;
	points = 0;
	img_points = font->createText("0");

	event->addKeyEvent(this);
	screen->addDrawer(HUD_LAYER, this);
}

HUD::~HUD()
{
	event->removeKeyEvent(this);
	screen->removeDrawer(HUD_LAYER, this);

	delete font;
	delete img_life;
	delete img_bomb;
	delete img_continue;
	delete img_points;
}

void HUD::draw()
{
	screen->blitImage(HUD_MARGIN_LEFT, HUD_MARGIN_TOP, img_points);

	for (int i = lifes; i--; )
	{
		screen->blitImage(SCREEN_WIDTH - HUD_MARGIN_RIGTH - (i + 1) * (img_life_width + HUD_MARGIN_SPAN), HUD_MARGIN_TOP, img_life);
	}

	for (int i = continues; i--; )
	{
		screen->blitImage(SCREEN_WIDTH - HUD_MARGIN_RIGTH - (i + 1) * (img_continue_width + HUD_MARGIN_SPAN), SCREEN_HEIGHT - HUD_MARGIN_BOTTOM - img_continue_height, img_continue);
	}

	for (int i = bombs; i--; )
	{
		screen->blitImage(HUD_MARGIN_LEFT + i * (img_bomb_width + HUD_MARGIN_SPAN), SCREEN_HEIGHT - HUD_MARGIN_BOTTOM - img_bomb_height, img_bomb);
	}
}

void HUD::keyDown(SDLKey key)
{
}

void HUD::keyUp(SDLKey key)
{
	if (key == SDLK_ESCAPE)
	{
		application->pause(!application->isPaused());
	}
}

void HUD::computePoints(int points)
{
	this->points += points;

	std::ostringstream sstream;
	sstream << points;
	delete img_points;
	img_points = font->createText(sstream.str());
}

void HUD::setLifes(int lifes)
{
	this->lifes = lifes;
}

void HUD::setContinues(int continues)
{
	this->continues = continues;
}

void HUD::setBombs(int bombs)
{
	this->bombs = bombs;
}
