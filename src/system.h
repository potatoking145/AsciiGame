#ifndef GREENFINGERS_SYSTEMS_SYSTEM_H_
#define GREENFINGERS_SYSTEMS_SYSTEM_H_

#include "components.h"
#include "tags.h"
#include "application.h"

namespace ecs_system
{
	class System
	{
	public:
		System() = default;
		~System() = default;
	};

	class Move : public System
	{
	public:
		Move(const char* name, application::Application* app)
		{
			app->ecs_world.system<comp_position, comp_velocity, comp_last_position>(name)
				.iter([](flecs::iter it, comp_position* Position, comp_velocity* Velocity, comp_last_position* LastPosition)
					{
						LastPosition->x = Position->x;
						LastPosition->y = Position->y;

						Position->x += Velocity->x;
						Position->y += Velocity->y;

						//TODO: Create a variable reset system
						Velocity->x = 0;
						Velocity->y = 0;
					});
		}
	};

	class Draw : public System
	{
	public:
		Draw(const char* name, application::Application* app)
		{
			app->ecs_world.system<comp_position, comp_char>(name)
				.iter([app](flecs::iter it, comp_position* Position, comp_char* Char)
					{
						TCOD_console_put_char(app->console.get(), Position->x, Position->y, Char->char_code, TCOD_BKGND_DEFAULT);
					});
		}
	};

	class PlayerController : public System
	{
	public:
		PlayerController(const char* name, application::Application* app)
		{
			app->ecs_world.system<tag_player, comp_velocity>(name)
				.iter([app](flecs::iter it, tag_player* ignore, comp_velocity* Velocity)
					{
						if (app->DidInputHappen(inputs::UP)) {
							Velocity->y = -1;
						}
						else if (app->DidInputHappen(inputs::DOWN)) {
							Velocity->y = 1;
						}
						else if (app->DidInputHappen(inputs::LEFT)) {
							Velocity->x = -1;
						}
						else if (app->DidInputHappen(inputs::RIGHT)) {
							Velocity->x = 1;
						}
					});
		}
	};
}

#endif