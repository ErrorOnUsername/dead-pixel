#pragma once

#include <Renderer/VertexArray.h>

namespace DP {
class GLVertexArray : public VertexArray {
public:
	GLVertexArray();
	~GLVertexArray();

	void bind() const override;
	void unbind() const override;

	void add_vertex_buffer(const shared_ptr<VertexBuffer>& vertex_buffer) override;
	void set_index_buffer(const shared_ptr<IndexBuffer>& index_buffer) override;

	const std::vector<shared_ptr<VertexBuffer>>& vertex_buffers() const override { return m_vertex_buffers; }
	const shared_ptr<IndexBuffer>& index_buffer() const override { return m_index_buffer; }

private:
	uint32_t m_id;
	uint32_t m_vertex_buffer_index = 0;
	std::vector<shared_ptr<VertexBuffer>> m_vertex_buffers;
	shared_ptr<IndexBuffer> m_index_buffer;
};
}