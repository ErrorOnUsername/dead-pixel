#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <initializer_list>

#include <Core/Pointer.h>

namespace DP {
enum class ShaderDataType {
	BOOL,
	INT, INT2, INT3, INT4,
	FLOAT, FLOAT2, FLOAT3, FLOAT4,
	MAT3, MAT4
};

static uint32_t shader_type_size(ShaderDataType type)
{
	switch (type) {
		case ShaderDataType::BOOL: return 1;

		case ShaderDataType::INT:
		case ShaderDataType::FLOAT: return 4;

		case ShaderDataType::INT2:
		case ShaderDataType::FLOAT2: return 4 * 2;

		case ShaderDataType::INT3:
		case ShaderDataType::FLOAT3: return 4 * 3;

		case ShaderDataType::INT4:
		case ShaderDataType::FLOAT4: return 4 * 4;

		case ShaderDataType::MAT3: return 4 * 3 * 3;
		case ShaderDataType::MAT4: return 4 * 4 * 4;
	}
}

struct BufferElement {
	BufferElement(ShaderDataType type, std::string& name, bool normalized = false)
		: type(type)
		, name(name)
		, normalized(normalized)
		, size(shader_type_size(type))
		, offset(0)
	{ }

	ShaderDataType type;
	std::string name;
	bool normalized;
	uint32_t size;
	size_t offset;

	uint32_t component_count() const
	{
		switch(type)
		{
			case ShaderDataType::BOOL:
			case ShaderDataType::INT:
			case ShaderDataType::FLOAT:  return 1;

			case ShaderDataType::INT2:
			case ShaderDataType::FLOAT2: return 2;

			case ShaderDataType::INT3:
			case ShaderDataType::FLOAT3:
			case ShaderDataType::MAT3:   return 3;

			case ShaderDataType::INT4:
			case ShaderDataType::FLOAT4:
			case ShaderDataType::MAT4:   return 4;
		}
	}
};

class BufferLayout {
public:
	BufferLayout() = default;
	BufferLayout(std::initializer_list<BufferElement> elements)
		: m_elements(elements)
	{
		calculate_offsets_and_stride();
	}

	uint32_t stride() const { return m_stride; }
	const std::vector<BufferElement>& elements() { return m_elements; }

	std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_elements.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

private:
	void calculate_offsets_and_stride()
	{
		size_t offset = 0;
		m_stride = 0;
		for(auto& element : m_elements)
		{
			element.offset = offset;
			offset += element.size;
			m_stride += element.size;
		}
	}

private:
	std::vector<BufferElement> m_elements;
	uint32_t m_stride;
};

class VertexBuffer {
public:
	virtual ~VertexBuffer() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual void set_data(const void* data, uint32_t size) = 0;

	virtual const BufferLayout& layout() const = 0;
	virtual void set_layout(const BufferLayout& layout) = 0;

	static shared_ptr<VertexBuffer> create(uint32_t size);
	static shared_ptr<VertexBuffer> create(const void* data, uint32_t size);
};

class IndexBuffer {
public:
	virtual ~IndexBuffer() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual uint32_t count() const = 0;

	static shared_ptr<IndexBuffer> create(uint32_t* indices, uint32_t count);
};
}