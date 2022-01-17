#pragma once

#include <glm/glm.hpp>

#include <gfx/camera.hh>
#include <gfx/ui/ui_theme.hh>

namespace DP::UI {

struct Panel {
	glm::vec2 position;
	float     width;
	float     height;
};

enum class Layout {
	Vertical,
	Horizontal
};

void set_theme(UITheme*);

void begin(char const* name, OrthographicCamera const&, Layout);
void begin_child(char const* name, Layout);
void end_child();
void end();

bool button(char const* label);

}
