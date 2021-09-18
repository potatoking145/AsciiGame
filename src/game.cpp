#include "game.h"

void game::Game::Init()
{
	_ctx.global_ctx->ecs_worlds["game"] = &_ecs_world;

	//TODO: Create .ini file for these settings and create code to load it
	_ctx.console = tcod::new_console(80, 25);
	_ecs_world.set_target_fps(60);

	_interface.InitContext();
}