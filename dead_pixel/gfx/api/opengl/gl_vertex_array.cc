#include <glad/glad.h>

#include <gfx/vertex_array.hh>

namespace DP {

static GLint shader_type_to_gl_type(ShaderDataType data_type)
{
	switch(data_type) {
		case ShaderDataType::Bool:   return GL_BOOL;
		case ShaderDataType::Int:    return GL_INT;
		case ShaderDataType::Int2:   return GL_INT;
		case ShaderDataType::Int3:   return GL_INT;
		case ShaderDataType::Int4:   return GL_INT;
		case ShaderDataType::Float:  return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Mat3:   return GL_FLOAT;
		case ShaderDataType::Mat4:   return GL_FLOAT;
	}
}

VertexArray::VertexArray()
	: array_id(0)
	, vertex_buffer_index(0)
{
	glGenVertexArrays(1, &array_id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &array_id);
}

void VertexArray::bind()
{
	glBindVertexArray(array_id);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::set_index_buffer(RefPtr<IndexBuffer> const& buffer)
{
	bind();
	buffer->bind();

	index_buffer = buffer;
}

void VertexArray::add_vertex_buffer(RefPtr<VertexBuffer> const& buffer)
{
	ASSERT(buffer->buffer_layout.elements.size(), "vertex buffer has no layout!!!");

	bind();
	buffer->bind();

	auto const& layout   = buffer->buffer_layout;
	auto const& elements = layout.elements;
	for(auto const& element : elements) {
		switch(element.type) {
			case ShaderDataType::Bool:
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4: {
				glEnableVertexAttribArray(vertex_buffer_index);
				glVertexAttribIPointer(vertex_buffer_index
				                     , element.component_count()
				                     , shader_type_to_gl_type(element.type)
				                     , layout.stride
									 , (void const*)element.offset);

				vertex_buffer_index++;
				break;
			}

			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4: {
				glEnableVertexAttribArray(vertex_buffer_index);
				glVertexAttribPointer(vertex_buffer_index
				                    , element.component_count()
				                    , shader_type_to_gl_type(element.type)
				                    , element.is_normalized ? GL_TRUE : GL_FALSE
				                    , layout.stride
				                    , (void const*)element.offset);

				vertex_buffer_index++;
				break;
			}

			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4: {
				auto count = element.component_count();
				for(u32 i = 0; i < count; i++) {
					glEnableVertexAttribArray(vertex_buffer_index);
					glVertexAttribPointer(vertex_buffer_index
					                    , count
					                    , shader_type_to_gl_type(element.type)
					                    , element.is_normalized ? GL_TRUE : GL_FALSE
					                    , layout.stride
					                    , (const void*)(element.offset + sizeof(float) * count * i));
					glVertexAttribDivisor(vertex_buffer_index, 1);
					vertex_buffer_index++;
				}
				break;
			}
		}
	}
	vertex_buffers.push_back(buffer);
}

}
