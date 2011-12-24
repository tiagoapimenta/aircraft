#ifndef INTERFACES_H
#define INTERFACES_H

class IKeyEventHandleable
{
public:
	virtual void keyDown(SDLKey key) = 0;
	virtual void keyUp(SDLKey key) = 0;
};

class IUpdatable
{
public:
	virtual void update() = 0;
};

class IDrawable
{
public:
	virtual void draw() = 0;
};

#endif
