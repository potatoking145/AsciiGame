#include "game.h"
#include "components.h"
#include "inputs.h"

void game::Game::PlayerController()
{
	auto velocity = _ecs_world.entity(1)
		.set<comp_velocity>({ 0, 0 }) // reset velocity
		.get_mut<comp_velocity>(); // get editable velocity

	if (DidInputHappen(inputs::UP)) {
		velocity->y = -1;
	}
	else if (DidInputHappen(inputs::DOWN)) {
		velocity->y = 1;
	}
	else if (DidInputHappen(inputs::LEFT)) {
		velocity->x = -1;
	}
	else if (DidInputHappen(inputs::RIGHT)) {
		velocity->x = 1;
	}
}

void game::Game::Init()
{
	global_ctx->ecs_worlds["game"] = &_ecs_world;

	//TODO: Create .ini file for these settings and create code to load it
	console = tcod::new_console(80, 25);
	_ecs_world.set_target_fps(60);
	app_interface.InitContext("Greenfingers", true, SDL_WINDOW_RESIZABLE, TCOD_RENDERER_SDL2, &console);

	_ecs_world.entity(1) // player
		.set<comp_position>({ 0, 0 })
		.set<comp_last_position>({ 0, 0 })
		.set<comp_velocity>({ 0, 0 })
		.set<comp_char>({ '@' });
}