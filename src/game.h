#ifndef GREENFINGERS_GAME_GAME_H_
#define GREENFINGERS_GAME_GAME_H_

#include "application.h"
#include "system.h"

namespace game {
	class Game : public application::Application
	{
	private:
		ecs_system::sysMove _move_system = ecs_system::sysMove("move", &_ecs_world, &_ctx);
		ecs_system::sysDraw _draw_system = ecs_system::sysDraw("draw", &_ecs_world, &_ctx);
	public:
		Game() = default;
		~Game() = default;

		void Init();
	};
}

#endif