#ifndef UTIL_H
#define UTIL_H

#include "core.h"

class Util
{
public:
	static Util &getInstance();

	SDL_Surface *loadImage(std::string filename);
	void startCounter();
	void waitFPS();
	void quit();

protected:

private:
	static Util *instance;
	Uint32 timer, elapsed_time;

	Util();
};

#endif // UTIL_H

