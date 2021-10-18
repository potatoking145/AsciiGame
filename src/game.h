#ifndef GREENFINGERS_GAME_GAME_H_
#define GREENFINGERS_GAME_GAME_H_

#include "application.h"
#include "system.h"

namespace game {
	class Game : public application::Application
	{
	private:
		ecs_system::Move _move_system = ecs_system::Move("move", this);
		ecs_system::Draw _draw_system = ecs_system::Draw("draw", this);
		ecs_system::PlayerController _player_controller_system = ecs_system::PlayerController("player_controller", this);
	public:
		Game() = default;
		~Game() = default;

		void Init();
	};
}

#endif