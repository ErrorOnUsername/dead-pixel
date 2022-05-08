#pragma once
#include <unordered_map>

#include <core/uuid.hh>
#include <entity_system/entity.hh>

namespace DP {

struct EntityContext {
	static constexpr usize MAX_ENTITY_COUNT = 500;

	Entity*                         entity_table;
	std::unordered_map<UUID, usize> id_index_lookup;

	EntityContext();

	Entity* request_new();
	Entity* from_id(UUID id);
};

}
