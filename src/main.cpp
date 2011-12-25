#include "main.h"

int main(int argc, char *argv[])
{
	int ret = 0;

	Application *application = new Application();

	ret = application->gameLoop();

	delete application;

	return ret;
}

