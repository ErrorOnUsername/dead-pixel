#include "entity_context.hh"

#include <core/assert.hh>
#include <core/types.hh>
namespace DP {

EntityContext::EntityContext()
	: entity_table(new Entity[MAX_ENTITY_COUNT])
	, id_index_lookup()
{ }

Entity* EntityContext::request_new()
{
	for(usize i = 0; i < MAX_ENTITY_COUNT; i++) {
		if(entity_table[i].id == 0) {
			UUID id = { };

			entity_table[i].id = id;

			ASSERT(!id_index_lookup.contains(id), "UUID already exists!");
			id_index_lookup[id] = i;

			return &entity_table[i];
		}
	}

	ASSERT(false, "We've reached the maximum amount of entities for this scene");
	return nullptr;
}

Entity* EntityContext::from_id(UUID id)
{
	if(id_index_lookup.contains(id)) {
		return &entity_table[id_index_lookup.at(id)];
	}

	return nullptr;
}

}
