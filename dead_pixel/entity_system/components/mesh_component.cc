#include "mesh_component.hh"

#include <gfx/buffer.hh>
#include <gfx/shader.hh>

namespace DP {

MeshComponent::MeshComponent()
	: mesh_va(nullptr)
	, mesh_shader(nullptr)
{ }

MeshComponent::~MeshComponent()
{
	if(mesh_va)     delete mesh_va;
	if(mesh_shader) delete mesh_shader;
}

void MeshComponent::set_data(float* vertices, u32 vert_count, u32* indices, u32 index_count)
{
	mesh_va = new VertexArray();

	VertexBuffer* vb = new VertexBuffer(vertices, vert_count * sizeof(float));
	IndexBuffer*  ib = new IndexBuffer(indices, index_count);

	DP::BufferLayout buffer_layout = {
		{ DP::ShaderDataType::Float3, "in_position" },
		{ DP::ShaderDataType::Float3, "in_normal"   },
	};

	vb->buffer_layout = buffer_layout;

	mesh_va->add_vertex_buffer(vb);
	mesh_va->set_index_buffer(ib);

	mesh_shader = new Shader("dead_pixel/default_assets/shaders/default.vert"
	                       , "dead_pixel/default_assets/shaders/default.frag");
}

}
