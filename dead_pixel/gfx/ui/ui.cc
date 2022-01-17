#include "ui.hh"

#include <core/assert.hh>
#include <gfx/ui/ui_renderer.hh>

namespace DP::UI {

static constexpr float  DEFAULT_PANEL_WIDTH  = 100.0f;
static constexpr float  DEFAULT_PANEL_HEIGHT = 100.0f;
static constexpr size_t MAX_PANEL_COUNT      = 16;

static Panel* panels[MAX_PANEL_COUNT];
static Panel* current_panel = nullptr;

static UITheme* current_theme = nullptr;

static Panel* create_panel(char const* name)
{
	size_t next_open_panel_index = 0;
	bool   is_panel_index_available = false;

	for(size_t i = 0; i < MAX_PANEL_COUNT; i++) {
		if(!panels[i]) {
			next_open_panel_index = i;
			is_panel_index_available = true;
			break;
		}

		is_panel_index_available = false;
	}

	ASSERT(is_panel_index_available, "MAX_PANEL_COUNT exceeded!");

	Panel* panel    = (Panel*)malloc(sizeof(Panel));
	panel->id       = next_open_panel_index;
	panel->name     = name;
	panel->position = { 2.0f, 2.0f };
	panel->size     = { DEFAULT_PANEL_WIDTH, DEFAULT_PANEL_HEIGHT };

	panels[next_open_panel_index] = panel;
	return panel;
}

void set_theme(UITheme* theme)
{
	current_theme = theme;
}

void begin_panel(char const* panel_name, OrthographicCamera const& camera, Layout layout)
{
	ASSERT(!current_panel, "You cannot begin another panel while anoter panel is bound!");

	bool   panel_exists = false;
	size_t panel_index = 0;
	for(size_t i = 0; i < MAX_PANEL_COUNT; i++) {
		if(panels[i]) {
			// The pointers should be the same. That way two panels could have
			// the same name, but not collide.
			panel_exists = panels[i]->name == panel_name;
			panel_index  = i;
		}
	}

	if(!panel_exists)
		current_panel = create_panel(panel_name);
	else
		current_panel = panels[panel_index];

	UIRenderer::begin(camera);

	UIRenderer::fill_rect(current_panel->position
	                    , current_panel->size
	                    , { 0.6f, 0.6f, 0.6f, 1.0f });
}

void begin_child(char const*, Layout) { }

void end_child() { }

void end_panel()
{
	UIRenderer::end();

	current_panel = nullptr;
}

bool button(char const* label) { return false; }

}
