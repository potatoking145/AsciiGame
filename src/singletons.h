#ifndef GREENFINGERS_COMPONENTS_SINGLETONS_H_
#define GREENFINGERS_COMPONENTS_SINGLETONS_H_

struct singleton_collidable_entites_map
{
	std::array<std::array<flecs::entity*, WORLD_HEIGHT>, WORLD_WIDTH> map{};
};

#endif