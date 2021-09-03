#include <iostream>
#include <unordered_map>
#include <libtcod/libtcod.h>
#include <sdl/SDL.h>
//std::unordered_multimap<

int main(int argc, char* argv[])
{
	tcod::ConsolePtr console = tcod::new_console(80, 25);

	TCOD_ContextParams params{};
	params.tcod_version = TCOD_COMPILEDVERSION;  // This is required.
	params.columns = console->w;  // Derive the window size from the console size.
	params.rows = console->h;
	// params.console = console.get();  // New in version 1.19, this replaces the above two lines.
	params.window_title = "Libtcod Project";
	params.vsync = true;
	params.argc = argc;  // This allows some user-control of the context.
	params.argv = argv;

	tcod::ContextPtr context = tcod::new_context(params);

	tcod::print(*console, 0, 0, "Hello World", nullptr, nullptr, TCOD_BKGND_SET, TCOD_LEFT);

	while (true) {
		context->present(*console);  // Updates the visible display.

		SDL_Event event;
		SDL_WaitEvent(nullptr);  // Optional, sleep until events are available.
		while (SDL_PollEvent(&event)) {
			std::cout << event.key.keysym.sym << std::endl;

			switch (event.type) {
			case SDL_QUIT:
				return 0;  // Exit.
			}

			if (event.key.keysym.sym == SDLK_F1) {
				tcod::print(*console, 0, 1, "HERE!!!!!", nullptr, nullptr, TCOD_BKGND_SET, TCOD_LEFT);
				std::cout << "h" << std::endl;
			}
		}
	}

	return 0;
}