#include "system.h"
#include "application.h"

bool ecs_system::Move::MoveEntity(application::Application* app, flecs::entity* e, comp_position* p, comp_velocity* v, bool collide)
{
	bool result = true;

	auto col_map = app->ecs_world.get<singleton_collidable_entites_map>()->map;
	auto map = app->ecs_world.get<singleton_entites_map>()->map;

	//for (int x = 0; x < WORLD_WIDTH; ++x) {
	//	for (int y = 0; y < WORLD_HEIGHT; ++y) {

	//	}
	//}

	//clear old
	map.at(p->x).at(p->y) = nullptr;

	p->x += v->x;
	p->y += v->y;

	//set new
	map.at(p->x).at(p->y) = e;

	//Collision Check
	if (collide == true) {
		auto entity = map.at(p->x).at(p->y);

		//Find Collision
		if (entity != nullptr && entity != e) {
			col_map.at(p->x).at(p->y) = nullptr;

			//Reset Entity 1 Position
			p->x -= v->x;
			p->y -= v->y;

			col_map.at(p->x).at(p->y) = e;

			auto position = entity->get_mut<comp_position>();
			auto velocity = entity->get<comp_velocity>();

			col_map.at(position->x).at(position->y) = nullptr;

			//Reset Entity 2 Position
			position->x -= velocity->x;
			position->y -= velocity->y;

			col_map.at(position->x).at(position->y) = entity;

			result = false;
		}
	}

	return result;
}