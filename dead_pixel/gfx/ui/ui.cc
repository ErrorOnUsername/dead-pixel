#include "ui.hh"

#include <gfx/ui/ui_renderer.hh>

namespace DP::UI {

static UITheme* current_theme = nullptr;

void set_theme(UITheme* theme)
{
	current_theme = theme;
}

void begin(char const*, OrthographicCamera const& camera, Layout layout)
{
	UIRenderer::begin(camera);
}

void begin_child(char const*, Layout) { }

void end_child() { }

void end()
{
	UIRenderer::end();
}

bool button(char const* label) { return false; }

}
