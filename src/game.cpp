#include "game.h"
#include "components.h"

void game::Game::Init()
{
	_ctx.global_ctx->ecs_worlds["game"] = &_ecs_world;

	//TODO: Create .ini file for these settings and create code to load it
	_ctx.console = tcod::new_console(80, 25);
	_ecs_world.set_target_fps(60);
	_interface.InitContext("Greenfingers", true, SDL_WINDOW_RESIZABLE, TCOD_RENDERER_SDL2, &_ctx.console);

	_ecs_world.entity() //test entity
		.set<comp_position>({ 1,1 })
		.set<comp_char>({ 'A' });
}