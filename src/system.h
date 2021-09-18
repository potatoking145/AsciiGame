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

		~System() = default;

		System(const char* _name)
		{
			name = _name;
		}

		virtual void Init(flecs::world*, application::ApplicationCtx*)
		{
			std::wcout << "System(" << name.c_str() << "has no Init overload." << std::endl;
		}
	};

	class sysMove : public System
	{
	public:
		sysMove(const char* _name, flecs::world* world, application::ApplicationCtx* ctx) : System(_name) {};

		void Init(flecs::world* world, application::ApplicationCtx* ctx)
		{
			world->system<comp_position, comp_velocity, comp_last_position>(name.c_str())
				.ctx(ctx)
				.iter([](flecs::iter it, comp_position* Position, comp_velocity* Velocity, comp_last_position* LastPosition)
					{
						LastPosition->x = Position->x;
						LastPosition->y = Position->y;

						Position->x += Velocity->x;
						Position->y += Velocity->y;

						std::wcout << "Run" << std::endl;
					});
		}
	};
}

#endif