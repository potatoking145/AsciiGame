#ifndef GREENFINGERS_SYSTEMS_SYSTEM_H_
#define GREENFINGERS_SYSTEMS_SYSTEM_H_

#include "components.h"
#include "application.h"

namespace ecs_system
{
	class System
	{
	public:
		std::string name;

		System(const char* _name)
		{
			name = _name;
		}
		~System() = default;
	};

	class sysMove : public System
	{
	public:
		sysMove(const char* _name, flecs::world* world, application::ApplicationCtx* ctx) : System(_name)
		{
			world->system<comp_position, comp_velocity, comp_last_position>(name.c_str())
				.iter([](flecs::iter it, comp_position* Position, comp_velocity* Velocity, comp_last_position* LastPosition)
					{
						LastPosition->x = Position->x;
						LastPosition->y = Position->y;

						Position->x += Velocity->x;
						Position->y += Velocity->y;
					});
		}
	};

	class sysDraw : public System
	{
	public:
		sysDraw(const char* _name, flecs::world* world, application::ApplicationCtx* ctx) : System(_name)
		{
			world->system<comp_position, comp_char>(name.c_str())
				.ctx(ctx)
				.iter([ctx](flecs::iter it, comp_position* Position, comp_char* Char)
					{
						TCOD_console_put_char(ctx->console.get(), Position->x, Position->y, Char->char_code, TCOD_BKGND_DEFAULT);
					});
		}
	};
}

#endif