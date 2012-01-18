#include "main.h"

int main (int argc, char *argv[])
{
	int exit_code = 0;

	Application *application = new Application();

	exit_code = application->gameLoop();

	delete application;

	return exit_code;
}

