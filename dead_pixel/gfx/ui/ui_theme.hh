#pragma once
#include <cstdint>

namespace DP::UI {

struct UITheme {
	uint32_t primary_color;
	uint32_t neutral_color;
	uint32_t hover_color;
	uint32_t accent_color;

	uint32_t text_foreground;
};

}
