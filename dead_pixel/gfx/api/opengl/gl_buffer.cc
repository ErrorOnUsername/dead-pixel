#include <glad/glad.h>

#include <gfx/buffer.hh>

namespace DP {

// =================
// | Vertex Buffer |
// =================

VertexBuffer::VertexBuffer(u32 size)
{
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(float* vertices, u32 size)
{
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &buffer_id);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::set_data(void const* data, u32 size)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

// =================
// | Index Buffer  |
// =================

IndexBuffer::IndexBuffer(u32* indices, u32 size)
	: count(size)
{
	glGenBuffers(1, &buffer_id);

	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER,
	             size * sizeof(u32),
	             indices,
	             GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &buffer_id);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}
