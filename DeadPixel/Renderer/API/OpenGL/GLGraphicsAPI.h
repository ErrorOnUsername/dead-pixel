#pragma once
#include <cstdint>

#include <glm/glm.hpp>

#include <Core/Pointer.h>
#include <Renderer/API/GraphicsAPI.h>

namespace DP {
class GLGraphicsAPI : public GraphicsAPI {
public:
	void init() override;
	void set_viewport(int32_t x, int32_t y, int32_t width, int32_t height) override;
	void set_clear_color(const glm::vec4& color) override;
	void clear() override;

	void draw_indexed(const shared_ptr<VertexArray>& vertex_array, uint32_t vertex_count) override;
};
}