#pragma once

#include <glm/glm.hpp>

#include <Core/Pointer.h>
#include <Renderer/VertexArray.h>

namespace DP {
class GraphicsAPI {
public:
	enum class API {
		None = 0,
		OpenGL = 1,
		Vulkan = 2
	};
public:
	virtual ~GraphicsAPI() = default;

	virtual void init() = 0;
	virtual void set_viewport(int32_t x, int32_t y, int32_t width, int32_t height) = 0;
	virtual void set_clear_color(const glm::vec4& color) = 0;
	virtual void clear() = 0;

	virtual void draw_indexed(const shared_ptr<VertexArray>& vertex_array, uint32_t vertex_count = 0) = 0;

	static API api() { return s_api; }
	static unique_ptr<GraphicsAPI> create();

private:
	static API s_api;
};
}