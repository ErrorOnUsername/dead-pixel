#pragma once

#include <glm/glm.hpp>

#include <Core/Memory.h>
#include <GFX/VertexArray.h>

namespace DP {

struct Renderer {
	static void clear();
	static void set_clear_color(float r, float g, float b, float a);

	static void enable_depth();
	static void disable_depth();

	static void draw_indexed(RefPtr<VertexArray> const&);
};

}
