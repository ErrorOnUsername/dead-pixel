#pragma once

#include <glad/glad.h>

#include <Renderer/Buffer.h>

namespace DP {
class GLVertexBuffer : public VertexBuffer {
public:
	GLVertexBuffer(uint32_t size);
	GLVertexBuffer(float* vertices, uint32_t size);
	virtual ~GLVertexBuffer();

	void bind() const override;
	void unbind() const override;

	void set_data(const void* data, uint32_t size) override;

	const BufferLayout& layout() const override { return m_layout; }
	void set_layout(const BufferLayout& layout) override { m_layout = layout; }

private:
	uint32_t m_id;
	BufferLayout m_layout;
};

class GLIndexBuffer : public IndexBuffer {
public:
	GLIndexBuffer(uint32_t* indices, uint32_t count);
	~GLIndexBuffer();

	void bind() const override;
	void unbind() const override;

	uint32_t count() const override { return m_count; }

private:
	uint32_t m_id;
	uint32_t m_count;
};
}