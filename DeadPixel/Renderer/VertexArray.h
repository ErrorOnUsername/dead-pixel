#pragma once
#include <cstdint>

#include <glad/glad.h>

#include <Core/Pointer.h>
#include <Renderer/Buffer.h>

namespace DP {
class VertexArray {
public:
	virtual ~VertexArray() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual void add_vertex_buffer(const shared_ptr<VertexBuffer>& vertex_buffer) = 0;
	virtual void set_index_buffer(const shared_ptr<IndexBuffer>& index_buffer) = 0;

	virtual const std::vector<shared_ptr<VertexBuffer>>& vertex_buffers() const = 0;
	virtual const shared_ptr<IndexBuffer>& index_buffer() const = 0;

	static shared_ptr<VertexArray> create();
};
}

