#include "entity_context.hh"

#include <core/assert.hh>
#include <core/types.hh>
namespace DP {

EntityContext::EntityContext()
	: last_id(0)
	, entity_table(new Entity[MAX_ENTITY_COUNT])
	, id_index_lookup()
{ }

Entity* EntityContext::request_new(char const* name)
{
	for(usize i = 0; i < MAX_ENTITY_COUNT; i++) {
		if(entity_table[i].id == 0) {
			u32 id = (last_id++) + 1;
			entity_table[i].id = id;

			ASSERT(!id_index_lookup.contains(id), "ID already exists!");
			id_index_lookup[id] = i;

			Entity* entity = &entity_table[i];
			entity->name = name;

			return entity;
		}
	}

	ASSERT(false, "We've reached the maximum amount of entities for this scene");
	return nullptr;
}

Entity* EntityContext::from_id(u32 id)
{
	if(id_index_lookup.contains(id)) {
		return &entity_table[id_index_lookup.at(id)];
	}

	return nullptr;
}

void EntityContext::for_each(void (*func)(Entity*))
{
	for(u32 id = 0; id < MAX_ENTITY_COUNT; id++) {
		if(id_index_lookup.contains(id)) {
			func(&entity_table[id_index_lookup.at(id)]);
		}
	}
}

}
