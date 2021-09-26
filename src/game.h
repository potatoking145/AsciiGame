#ifndef GREENFINGERS_GAME_GAME_H_
#define GREENFINGERS_GAME_GAME_H_

#include "application.h"
#include "system.h"

namespace game {
	class Game : public application::Application
	{
	private:
		ecs_system::sysMove _move_system = ecs_system::sysMove("move", &_ecs_world, this);
		ecs_system::sysDraw _draw_system = ecs_system::sysDraw("draw", &_ecs_world, this);

		void PlayerController();
	public:
		Game() = default;
		~Game() = default;

		void Init();
		inline void Progress()
		{
			if (app_interface.IfClosedClose(global_ctx->sdl_event))
			{
				_is_closed = true;
				return;
			}

			PlayerController();

			TCOD_console_clear(console.get());
			_ecs_world.progress(0); // 0 means that flecs will find the delta_time on its own
			app_interface.DisplayConsole(*console);
		}
	};
}

#endif