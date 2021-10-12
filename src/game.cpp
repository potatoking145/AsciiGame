#include "game.h"
#include "components.h"
#include "tags.h"
#include "singletons.h"

void game::Game::Init()
{
	global_ctx->ecs_worlds["game"] = &ecs_world;

	//TODO: Create .ini file for these settings and create code to load it
	console = tcod::new_console(80, 25);
	ecs_world.set_target_fps(60);
	app_interface.InitContext("Greenfingers", true, SDL_WINDOW_RESIZABLE, TCOD_RENDERER_SDL2, &console);

	ecs_world.entity(1) // player
		.set<comp_position>({ 0, 0 })
		.set<comp_velocity>({ 0, 0 })
		.set<comp_char>({ '@' })
		.add<tag_player>()
		.add<tag_collidable>();

	ecs_world.add<singleton_collidable_entites_map>();
}