#pragma once
#include <unordered_map>

#include <entity_system/entity.hh>

namespace DP {

struct EntityContext {
	static constexpr usize MAX_ENTITY_COUNT = 500;

	u32     last_id;
	Entity* entity_table;

	std::unordered_map<u32, usize>  id_index_lookup;

	EntityContext();

	Entity* request_new();
	Entity* from_id(u32 id);

	void for_each(void (*func)(Entity*));
};

}
