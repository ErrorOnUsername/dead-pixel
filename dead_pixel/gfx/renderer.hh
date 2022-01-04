#pragma once

#include <glm/glm.hpp>

#include <core/memory.hh>
#include <gfx/vertex_array.hh>
#include <gfx/ui/ui_theme.hh>

namespace DP {

struct Renderer {
	static void clear          ();
	static void set_clear_color(float r, float g, float b, float a);

	static void enable_depth ();
	static void disable_depth();

	static void draw_indexed(RefPtr<VertexArray> const&, size_t index_count = 0);

	static void draw_ui_frame(glm::vec2 position, glm::vec2 size, UI::UITheme const&);
	static void draw_ui_rect (glm::vec2 position, glm::vec2 size, UI::UITheme const&);
	static void draw_ui_text (glm::vec2 position, glm::vec2 size, UI::UITheme const&);
};

}
