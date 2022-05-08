#pragma once

#include <core/memory.hh>
#include <gfx/vertex_array.hh>
#include <gfx/shader.hh>

namespace DP {

struct MeshComponent {
	RefPtr<VertexArray> mesh_va;
	RefPtr<Shader>      mesh_shader;
};

}
