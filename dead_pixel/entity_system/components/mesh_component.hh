#pragma once

#include <gfx/vertex_array.hh>
#include <gfx/shader.hh>

namespace DP {

struct MeshComponent {
	VertexArray* mesh_va;
	Shader*      mesh_shader;

	MeshComponent();
	~MeshComponent();

	void set_data(float* vertices, u32 vert_count, u32* indices, u32 index_count);
};

}
