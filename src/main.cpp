#include "window.h"

int main(int argc, char* args[])
{
	window::HideConsole();

	tcod::ConsolePtr console = tcod::new_console(80, 25);

	window::ApplicationInterface app;

	SDL_Event event;
	while (true) {
		app.DisplayConsole(*console);

		while (SDL_PollEvent(&event)) {
			if (app.IfClosedClose(&event)) {
				std::cout << "CLosed!!!";
				goto end;
			}

			std::wcout << event.window.event << std::endl;
			//std::cout << event.key.keysym.sym << std::endl;
			if (event.key.keysym.sym == SDLK_F1) {
				tcod::print(*console, 0, 1, "HERE!!!!!", nullptr, nullptr, TCOD_BKGND_SET, TCOD_LEFT);
			}

			if (event.key.keysym.sym == SDLK_TILDE) {
				window::ShowConsole();
			}
		}
	}

end:
	return 0;
}
