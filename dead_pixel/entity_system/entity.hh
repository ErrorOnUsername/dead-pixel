#pragma once

#include <core/types.hh>
#include <entity_system/components/transform_component.hh>

namespace DP {

enum class EntityComponentMask : u32 {
	None = 0,

	Transform = 0x01,
};

struct Entity {
	u32 id;
	u32 component_bitfield;

	TransformComponent transform;
};

}
