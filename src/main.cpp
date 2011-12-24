#include "main.h"

int main(int argc, char *argv[])
{
	Application *application = Application::getInstance();

	return application->gameLoop();
}

