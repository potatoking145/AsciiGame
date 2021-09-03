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

<<<<<<< HEAD
	tcod::ContextPtr context = tcod::new_context(params);

	tcod::print(*console, 0, 0, "Hello World", nullptr, nullptr, TCOD_BKGND_SET, TCOD_LEFT);

	while (true) {
		context->present(*console);  // Updates the visible display.
=======
std::map<flecs::entity_t, flecs::entity> entities;
flecs::world world;

void save()
{
	std::ofstream os("out.cereal", std::ios::binary);
	cereal::BinaryOutputArchive outa(os);

	for (auto const& [id, e] : entities) {
		outa(id);

		if (e.is_alive() == false) {
			outa(false);
			continue; //skips trying to add components from a dead entity
		} else { outa(true); }

		auto c_position = e.get<position>();
		if (c_position != nullptr) {
			outa(1);
			position comp{ c_position->x, c_position->y };
			outa(comp);
		}

		auto c_name = e.get<name>();
		if (c_name != nullptr) {
			outa(2);
			name comp{ c_name->n };
			outa(comp);
		}
		outa(0); //marks the end of the entity components
	}
	outa(4294967295); //marks the end of the save file
}

void load()
{
	std::ifstream is("out.cereal", std::ios::binary);
	cereal::BinaryInputArchive ina(is);

	flecs::entity_t t;
	int comp_id = 1; //not 0
	bool is_alive;
	flecs::entity entity;

	while (true) {
		ina(t);
		if (t == 4294967295) { break; } //reached the end

		entity = world.entity(t); //gets entity from entity id

		ina(is_alive);
		if (is_alive == false) {
			entity.destruct();
			continue;
		}
>>>>>>> 96b5e3dd810f3201bb6708ef96cf4bfe9b4b3a1c

		SDL_Event event;
		SDL_WaitEvent(nullptr);  // Optional, sleep until events are available.
		while (SDL_PollEvent(&event)) {
			std::cout << event.key.keysym.sym << std::endl;

<<<<<<< HEAD
			switch (event.type) {
			case SDL_QUIT:
				return 0;  // Exit.
			}
=======
		while (comp_id != 0) { //comp_id of 0 marks the end
			ina(comp_id);
>>>>>>> 96b5e3dd810f3201bb6708ef96cf4bfe9b4b3a1c

			if (event.key.keysym.sym == SDLK_F1) {
				tcod::print(*console, 0, 1, "HERE!!!!!", nullptr, nullptr, TCOD_BKGND_SET, TCOD_LEFT);
				std::cout << "h" << std::endl;
			}
		}
	}
<<<<<<< HEAD
=======
}

int main()
{
	entities[100001] = world.entity(100001)
		.set<position>({ 1,2 })
		.set<name>({ "entity_1" });

	entities[100002] = (world.entity(100002)
		.set<position>({ 5,10 })
		.set<name>({ "entity_2" }));

	entities[100002].destruct(); //testing entity death saving

	save();

	load();

	std::cout << entities[100002].is_alive();

	system("pause");
>>>>>>> 96b5e3dd810f3201bb6708ef96cf4bfe9b4b3a1c

	return 0;
}
