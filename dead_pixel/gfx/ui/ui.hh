#pragma once

#include <glm/glm.hpp>

#include <gfx/camera.hh>
#include <gfx/ui/ui_theme.hh>

namespace DP::UI {

struct Panel {
	size_t      id;
	char const* name;
	glm::vec2   position;
	glm::vec2   size;
};

enum class Layout {
	Vertical,
	Horizontal
};

void set_theme(UITheme*);

void begin_panel(char const* panel_name, OrthographicCamera const&, Layout);
void begin_child(char const* name, Layout);
void end_child();
void end_panel();

bool button(char const* label);

}
