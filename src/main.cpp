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

std::vector<flecs::entity> entities;
flecs::world world;

void save()
{
	std::ofstream os("out.cereal", std::ios::binary);
	cereal::BinaryOutputArchive outa(os);

	for (flecs::entity e : entities) {
		outa(e.id());
		std::cout << e.id() << std::endl;

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

		outa(0); //marks the end of the entity
	}
}

void load()
{
	std::ifstream is("out.cereal", std::ios::binary);
	cereal::BinaryInputArchive ina(is);

	flecs::entity_t t;
	int comp_id = 1; //not 0

	for(int i = 0; i <= entities.size(); i++) {
		ina(t);
		auto entity = world.entity(t);

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
	entities.push_back(world.entity(100001)
		.set<position>({ 1,2 })
		.set<name>({ "entity_1" }));

	entities.push_back(world.entity(100002)
		.set<position>({ 5,10 })
		.set<name>({ "entity_2" }));

	save();

	entities[0].set<name>({ "entity_bad 1" });
	entities[0].set<name>({ "entity_bad 2" });

	load();

	std::cout << entities[0].get<name>()->n << std::endl;
	std::cout << entities[1].get<name>()->n << std::endl;
	system("pause");

	return 0;
}