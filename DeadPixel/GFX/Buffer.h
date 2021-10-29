#pragma once

#include <dppch.h>
#include <Core/Assert.h>

namespace DP {

enum class ShaderDataType {
	Bool,
	Int,   Int2,   Int3,   Int4,
	Float, Float2, Float3, Float4,
	Mat3,  Mat4
};

struct BufferElement {
	char const*    name;
	ShaderDataType type;
	uint32_t       size;
	size_t         offset;
	bool           is_normalized;

	BufferElement() = default;
	BufferElement(ShaderDataType data_type,
	              char const* uniform_name,
	              bool normalized = false)
		: name(uniform_name)
		, type(data_type)
		, is_normalized(normalized)
	{ }

	uint32_t component_count() const
	{
		switch(type) {
			case ShaderDataType::Bool:   return 1;
			case ShaderDataType::Int:    return 1;
			case ShaderDataType::Int2:   return 2;
			case ShaderDataType::Int3:   return 3;
			case ShaderDataType::Int4:   return 4;
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat3:   return 3; // 3 vec3s
			case ShaderDataType::Mat4:   return 4; // 4 vec4s
		}

		// It's literally impossible to reach this. So we're just gonna
		// assert false.
		ASSERT(false, "Unknown shader data type! HOW??");
		return 0;
	}
};

struct BufferLayout {
	std::vector<BufferElement> elements;
	uint32_t                   stride;

	BufferLayout() { };
	BufferLayout(std::initializer_list<BufferElement> initializer_elements)
		: elements(initializer_elements)
	{ }
private:
	void calculate_offsets_and_stride()
	{
		size_t offset = 0;
		stride = 0;

		for(auto& element : elements) {
			element.offset = offset;
			offset += element.size;
			stride += element.size;
		}
	}
};

struct VertexBuffer {
	uint32_t     buffer_id; // TODO: Find out if this applies in Vulkan as well
	BufferLayout buffer_layout;

	VertexBuffer(uint32_t size);
	VertexBuffer(float* vertices, uint32_t size);
	~VertexBuffer();

	void bind  () const;
	void unbind() const;

	void set_data(void const* data, uint32_t size);
};

struct IndexBuffer {
	uint32_t buffer_id;
	uint32_t count;

	IndexBuffer(uint32_t* vertices, uint32_t size);
	~IndexBuffer();

	void bind  () const;
	void unbind() const;
};

}
