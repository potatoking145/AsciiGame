#include <iostream>
#include <libtcod/libtcod.hpp>
#include <flecs.h>
#include <string>
#include <sstream>
#include <fstream>

struct ex
{
	int x;
	int y;
};


int main()
{
	std::cout << "Hello World!" << std::endl;

	flecs::world world;
	auto test = world.entity();
	world.component<ex>();
	test.set<ex>({ 900300404, 50 });

	auto q = world.query_builder<ex>()
		.build();

	q.each([](flecs::entity e, ex& x) {
		//do nothing
	});


	//TCODConsole::initRoot(60, 60, "Empty", false, TCOD_RENDERER_SDL);
	//TCODSystem::setFps(60);

	return 0;
}
