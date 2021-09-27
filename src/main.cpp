#include "application.h"
#include "game.h"
#include "window.h"

inline void ProcessCommandArguments(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++) { // check for command line arguments
		if (strcmp(argv[i], "--debug") == 0 || strcmp(argv[i], "-d") == 0) {
			window::ShowConsole();
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	window::HideConsole(); // by default hide the console

	ProcessCommandArguments(argc, argv);

	SDL_Event event; // contains window events such as resizing, moving, key press, mouse movments, etc.
	auto AppManager = application::ApplicationManager(&event);
	AppManager.CreateApplication<game::Game>();

	while (!AppManager.is_closed) {
		SDL_PollEvent(&event); // gets whatever the current event is, also updates the active windows--meaning they can be moved and resized, etc.
		AppManager.ProgressApplications();
	}

	TCOD_quit();

	return 0;
}