#pragma once
#include <vector>

#include <core/types.hh>
#include <core/assert.hh>

namespace DP {

enum class ShaderDataType {
	Bool,
	Int,   Int2,   Int3,   Int4,
	Float, Float2, Float3, Float4,
	Mat3,  Mat4,
};

static u32 shader_data_type_size(ShaderDataType data_type)
{
	switch(data_type) {
		case ShaderDataType::Bool:   return 1;
		case ShaderDataType::Int:    return 4;
		case ShaderDataType::Int2:   return 4*2;
		case ShaderDataType::Int3:   return 4*3;
		case ShaderDataType::Int4:   return 4*4;
		case ShaderDataType::Float:  return 4;
		case ShaderDataType::Float2: return 4*2;
		case ShaderDataType::Float3: return 4*3;
		case ShaderDataType::Float4: return 4*4;
		case ShaderDataType::Mat3:   return 4*3*3;
		case ShaderDataType::Mat4:   return 4*4*4;
	}
}

struct BufferElement {
	char const*    name;
	ShaderDataType type;
	u32            size;
	usize          offset;
	bool           is_normalized;

	BufferElement() = default;
	BufferElement(ShaderDataType data_type,
	              char const* uniform_name,
	              bool normalized = false)
		: name(uniform_name)
		, type(data_type)
		, size(shader_data_type_size(data_type))
		, offset(0)
		, is_normalized(normalized)
	{ }

	u32 component_count() const
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
		ASSERT(false, "Unknown ShaderDataType... how??");
		return 0;
	}
};

struct BufferLayout {
	std::vector<BufferElement> elements;
	u32                        stride;

	BufferLayout() { }
	BufferLayout(std::initializer_list<BufferElement> initializer_elements)
		: elements(initializer_elements)
	{
		calculate_offsets_and_stride();
	}

private:
	void calculate_offsets_and_stride()
	{
		stride = 0;

		for(auto& element : elements) {
			element.offset = stride;
			stride += element.size;
		}
	}
};

struct VertexBuffer {
	u32          buffer_id;
	BufferLayout buffer_layout;

	VertexBuffer(u32 size);
	VertexBuffer(float* vertices, u32 size);
	~VertexBuffer();

	void bind  () const;
	void unbind() const;

	void set_data(void const* data, u32 size);
};

struct IndexBuffer {
	u32 buffer_id;
	u32 count;

	IndexBuffer(u32* indices, u32 size);
	~IndexBuffer();

	void bind  () const;
	void unbind() const;
};

}
