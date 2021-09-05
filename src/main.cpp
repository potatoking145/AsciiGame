#include "window.h"

int main(int argc, char* args[])
{
	window::HideConsole();

	tcod::ConsolePtr console = tcod::new_console(80, 25);

	//window::ApplicationInterface app;

	TCOD_ContextParams params{};
	params.tcod_version = TCOD_COMPILEDVERSION;  // This is required.
	params.columns = console->w;  // Derive the window size from the console size.
	params.rows = console->h;
	params.window_title = "Libtcod Project";
	params.vsync = true;
	params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
	params.renderer_type = TCOD_RENDERER_SDL2;

	tcod::ContextPtr context = tcod::new_context(params);

	tcod::print(*console, 0, 0, "Hello World", nullptr, nullptr, TCOD_BKGND_SET, TCOD_LEFT);

	while (true) {
		context->present(*console);  // Updates the visible display.
		SDL_Event event;
		SDL_WaitEvent(nullptr);  // Optional, sleep until events are available.

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			}

			std::cout << event.key.keysym.sym << std::endl;
			if (event.key.keysym.sym == SDLK_F1) {
				tcod::print(*console, 0, 1, "HERE!!!!!", nullptr, nullptr, TCOD_BKGND_SET, TCOD_LEFT);
			}

			if (event.key.keysym.sym == SDLK_TILDE) {
				window::ShowConsole();
			}
		}
	}

	return 0;
}
