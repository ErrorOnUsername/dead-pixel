#pragma once

#include <glm/glm.hpp>

#include <gfx/camera.hh>

namespace DP::UI {

struct UIRenderer {
	static void init();
	static void shutdown();

	static void begin(OrthographicCamera const&);
	static void begin_next_batch();
	static void next_batch();
	static void end();
	static void flush();

	static void fill_rect(glm::vec2 const& positon,   glm::vec2 const& size, glm::vec4 const& color);
	static void fill_rect(glm::vec3 const& positon,   glm::vec2 const& size, glm::vec4 const& color);
	static void fill_rect(glm::mat4 const& transform, glm::vec4 const& color);
};

}
