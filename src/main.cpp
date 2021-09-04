#include <iostream>
#include <unordered_map>
#include <libtcod/libtcod.h>
#include <sdl/SDL.h>
#include <flecs.h>
//std::unordered_multimap<

struct mod__moveposition
{
	struct comp__position {
		uint8_t x, y;
	};

	mod__moveposition(flecs::world& world)
	{
		world.module<mod__moveposition>();

		world.pod_component<comp__position>();
	}
};


int main(int argc, char* args[])
{
	flecs::world world;
	auto mod = world.import<mod__moveposition>();
	auto test = world.entity();
	test.set<mod__moveposition::comp__position>({10, 35});

	tcod::ConsolePtr console = tcod::new_console(80, 25);

	TCOD_ContextParams params{};
	params.tcod_version = TCOD_COMPILEDVERSION;  // This is required.
	params.columns = console->w;  // Derive the window size from the console size.
	params.rows = console->h;
	params.window_title = "Libtcod Project";
	params.vsync = true;
	params.sdl_window_flags = SDL_WINDOW_RESIZABLE;

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
				std::cout << "h" << std::endl;
			}
		}
	}
}
