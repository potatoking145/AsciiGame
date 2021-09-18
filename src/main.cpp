#include "application.h"
#include "game.h"

int main(int argc, char* argv[])
{
	SDL_Event event;
	auto AppManager = application::ApplicationManager(&event);
	AppManager.CreateApplication<game::Game>();

	while (!AppManager.is_closed) {
		SDL_PollEvent(&event);
		AppManager.ProgressApplications();
	}

	TCOD_quit();

	return 0;
}