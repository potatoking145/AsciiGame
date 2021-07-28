#include <iostream>
#include <entt.hpp>
#include <libtcod.hpp>

int main()
{
	std::cout << "Hello World!";

	TCODConsole::initRoot(60, 60, "Empty", false, TCOD_RENDERER_SDL);
	TCODSystem::setFps(60);

	while(true) {}

	return 0;
}