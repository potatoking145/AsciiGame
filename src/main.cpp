#include "window.h"

int main(int argc, char* args[])
{
	tcod::ConsolePtr console = tcod::new_console(80, 25);
	window::ApplicationInterface app;

	SDL_Event event;
	while (true) {
		app.DisplayConsole(*console);

		while (SDL_PollEvent(&event)) {
			if (app.IfClosedClose(&event)) {
				std::cout << "CLosed!!!";
				return 0;
			}
		}
	}

	return 0;
}
