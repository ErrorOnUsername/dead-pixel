#pragma once

#include <core/memory.hh>
#include <gfx/buffer.hh>

namespace DP {

struct VertexArray {
	u32 array_id;
	u32 vertex_buffer_index;

	std::vector<RefPtr<VertexBuffer>> vertex_buffers;
	RefPtr<IndexBuffer>               index_buffer;

	VertexArray ();
	~VertexArray();

	static RefPtr<VertexArray> create() { return make_ref_ptr<VertexArray>(); }

	void bind  ();
	void unbind();

	void set_index_buffer (RefPtr<IndexBuffer> const&);
	void add_vertex_buffer(RefPtr<VertexBuffer> const&);
};

}
