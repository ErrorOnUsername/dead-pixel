#pragma once

#include <core/types.hh>
#include <entity_system/components/transform_component.hh>
#include <entity_system/components/mesh_component.hh>

namespace DP {

struct Entity {
	char const* name;

	u32 id;
	u32 component_bitfield;

	TransformComponent transform;
	MeshComponent      mesh;
};

}
