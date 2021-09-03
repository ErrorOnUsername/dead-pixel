#include "GLVertexArray.h"

#include <glad/glad.h>

#include <Renderer/Buffer.h>

namespace DP {
static GLenum shader_data_type_to_gl_type(ShaderDataType type)
{
	switch(type)
	{
		case ShaderDataType::BOOL: return GL_BOOL;

		case ShaderDataType::INT:
		case ShaderDataType::INT2:
		case ShaderDataType::INT3:
		case ShaderDataType::INT4: return GL_INT;

		case ShaderDataType::FLOAT:
		case ShaderDataType::FLOAT2:
		case ShaderDataType::FLOAT3:
		case ShaderDataType::FLOAT4:
		case ShaderDataType::MAT3:
		case ShaderDataType::MAT4: return GL_FLOAT;
	}
}

GLVertexArray::GLVertexArray()
{
	glCreateVertexArrays(1, &m_id);
}

GLVertexArray::~GLVertexArray()
{
	glDeleteVertexArrays(1, &m_id);
}

void GLVertexArray::bind() const
{
	glBindVertexArray(m_id);
}

void GLVertexArray::unbind() const
{
	glBindVertexArray(0);
}

void GLVertexArray::add_vertex_buffer(const shared_ptr<VertexBuffer>& vertex_buffer)
{
	bind();
	vertex_buffer->bind();

	const auto& layout = vertex_buffer->layout();
	for(const auto& element : layout)
	{
		switch(element.type)
		{
			case ShaderDataType::BOOL:
			case ShaderDataType::INT:
			case ShaderDataType::INT2:
			case ShaderDataType::INT3:
			case ShaderDataType::INT4:
			{
				glEnableVertexAttribArray(m_vertex_buffer_index);
				glVertexAttribIPointer(
					m_vertex_buffer_index,
					element.component_count(),
					shader_data_type_to_gl_type(element.type),
					layout.stride(),
					(const void*)element.offset
				);
				m_vertex_buffer_index++;
				break;
			}
			case ShaderDataType::FLOAT:
			case ShaderDataType::FLOAT2:
			case ShaderDataType::FLOAT3:
			case ShaderDataType::FLOAT4:
			{
				glEnableVertexAttribArray(m_vertex_buffer_index);
				glVertexAttribPointer(
					m_vertex_buffer_index,
					element.component_count(),
					shader_data_type_to_gl_type(element.type),
					element.normalized ? GL_TRUE : GL_FALSE,
					layout.stride(),
					(const void*)element.offset
				);
				m_vertex_buffer_index++;
				break;
			}
			case ShaderDataType::MAT3:
			case ShaderDataType::MAT4:
			{
				uint8_t count = element.component_count();
				for(uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_vertex_buffer_index);
					glVertexAttribPointer(
							m_vertex_buffer_index,
							element.component_count(),
							shader_data_type_to_gl_type(element.type),
							element.normalized ? GL_TRUE : GL_FALSE,
							layout.stride(),
							(const void*)(element.offset + sizeof(float) * count * i)
					);
					m_vertex_buffer_index++;
				}
				break;
			}
		}
	}
	m_vertex_buffers.push_back(vertex_buffer);
}

void GLVertexArray::set_index_buffer(const shared_ptr<IndexBuffer>& index_buffer)
{
	bind();
	index_buffer->bind();

	m_index_buffer = index_buffer;
}
}