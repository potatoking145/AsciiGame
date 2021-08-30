#include <iostream>
#include <flecs.h>
#include <string>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <fstream>

struct position
{
	int x;
	int y;

	template<class Archive>
	void serialize(Archive& ar) {
		ar(x, y);
	}
};

struct name
{
	std::string n;

	template<class Archive>
	void serialize(Archive& ar) {
		ar(n);
	}
};

struct extra
{
	flecs::entity_t dummy;

	template<class Archive>
	void serialize(Archive& ar) {
		ar(dummy);
	}
};

std::map<flecs::entity_t, flecs::entity> entities;
flecs::world world;

void save()
{
	std::ofstream os("out.cereal", std::ios::binary);
	cereal::BinaryOutputArchive outa(os);

	for (auto const& [id, e] : entities) {
		outa(id);

		if (e.is_alive() == false) {
			outa(false);

			continue; //skips trying to add components from a dead entity
		}
		else {
			outa(true);
		}

		auto c_position = e.get<position>();
		if (c_position != nullptr) {
			outa(1);
			position comp{ c_position->x, c_position->y };
			outa(comp);
		}

		auto c_name = e.get<name>();
		if (c_name != nullptr) {
			outa(2);
			name comp{ c_name->n };
			outa(comp);
		}

		outa(0); //marks the end of the entity components
	}

	outa(4294967295); //marks the end of the save file
}

void load()
{
	std::ifstream is("out.cereal", std::ios::binary);
	cereal::BinaryInputArchive ina(is);

	flecs::entity_t t;
	int comp_id = 1; //not 0
	bool is_alive;
	flecs::entity entity;

	while (true) {
		ina(t);
		if (t == 4294967295) { break; } //reached the end

		entity = world.entity(t); //gets entity from entity id

		ina(is_alive);
		if (is_alive == false) {
			entity.destruct();

			continue;
		};

		entities[entity.id()] = entity; //adds the entity if it does not already exist ;; note: is after checking for aliveness

		while (comp_id != 0) {
			ina(comp_id);

			switch (comp_id) {
			case 1:
				position c_pos;
				ina(c_pos);
				entity.set<position>({ c_pos.x, c_pos.y });
				break;
			case 2:
				name c_name;
				ina(c_name);
				entity.set<name>({ c_name.n });
				break;
			}
		}
	}
}

int main()
{
	entities[100001] = world.entity(100001)
		.set<position>({ 1,2 })
		.set<name>({ "entity_1" });

	entities[100002] = (world.entity(100002)
		.set<position>({ 5,10 })
		.set<name>({ "entity_2" }));

	entities[100002].destruct();

	save();

	load();

	std::cout << entities[100002].is_alive();

	system("pause");

	return 0;
}