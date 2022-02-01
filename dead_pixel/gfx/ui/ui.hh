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

enum FrameParams : uint8_t {
	FP_BORDERED          = 0b00000000,
	FP_BORDERLESS        = 0b00000001,
	FP_RESIZABLE         = 0b00000010,
	FP_CLOSEABLE         = 0b00000100,
	FP_UNCLOSABLE        = 0b00000000,
	FP_SHOW_TITLEBAR     = 0b00001000,
	FP_HIDE_TITLEBAR     = 0b00000000,
	FP_LAYOUT_HORIZONTAL = 0b00010000,
	FP_LAYOUT_VERTICAL   = 0b00000000,

	FP_DEFAULTS = FP_BORDERED || FP_RESIZABLE || FP_CLOSEABLE
	           || FP_SHOW_TITLEBAR || FP_LAYOUT_VERTICAL
};

void set_theme(UITheme*);

void begin_panel(char const* panel_name, OrthographicCamera const&, FrameParams);
void end_panel();

bool button(char const* label);

}
