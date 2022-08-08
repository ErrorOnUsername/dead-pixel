#pragma once

#include <gfx/buffer.hh>

namespace DP {

struct VertexArray {
	u32 array_id;
	u32 vertex_buffer_index;

	std::vector<VertexBuffer*> vertex_buffers;
	IndexBuffer*               index_buffer;

	VertexArray ();
	~VertexArray();

	void bind  ();
	void unbind();

	void set_index_buffer (IndexBuffer*);
	void add_vertex_buffer(VertexBuffer*);
};

}
