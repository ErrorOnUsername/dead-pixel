#include "GLBuffer.h"
#include <cstdint>

#include <glad/glad.h>

namespace DP {
//=================================================================================================
// Vertex Buffer ==================================================================================
//=================================================================================================
GLVertexBuffer::GLVertexBuffer(uint32_t size)
{
	glCreateBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

GLVertexBuffer::GLVertexBuffer(float* vertices, uint32_t size)
{
	glCreateBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

GLVertexBuffer::~GLVertexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void GLVertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void GLVertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLVertexBuffer::set_data(const void* data, uint32_t size)
{
	bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

//=================================================================================================
// Index Buffer ===================================================================================
//=================================================================================================
GLIndexBuffer::GLIndexBuffer(uint32_t* indices, uint32_t count)
	: m_count(count)
{
	glGenBuffers(1, &m_id);

	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

GLIndexBuffer::~GLIndexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void GLIndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void GLIndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}