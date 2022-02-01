#include "ui.hh"

#include <core/assert.hh>
#include <core/input.hh>
#include <core/mouse_code.hh>
#include <gfx/ui/ui_renderer.hh>

namespace DP::UI {

static constexpr float  DEFAULT_PANEL_WIDTH  = 100.0f;
static constexpr float  DEFAULT_PANEL_HEIGHT = 100.0f;
static constexpr float  RESIZE_REGION_WIDTH  = 10.0f;
static constexpr size_t MAX_PANEL_COUNT      = 16;

static Panel* panels[MAX_PANEL_COUNT];
static Panel* current_panel = nullptr;

static UITheme* current_theme = nullptr;

enum ResizeZone : uint8_t {
	STATE_NONE          = 0x00,
	STATE_RESIZE_LEFT   = 0x01,
	STATE_RESIZE_RIGHT  = 0x02,
	STATE_RESIZE_BOTTOM = 0x04,
	STATE_DRAG          = 0x08
};

static bool       is_drag_started = false;
static glm::vec2  start_delta     = { };
static uint8_t    current_state   = STATE_NONE;

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

static bool is_mouse_in_bounds(glm::vec2 const& mouse_position
                             , glm::vec2 const& rect_position
                             , glm::vec2 const& rect_size)
{
	return (mouse_position.x > rect_position.x && mouse_position.y > rect_position.y)
	    && (mouse_position.x < rect_position.x + rect_size.x && mouse_position.y < rect_position.y + rect_size.y);
}

void set_theme(UITheme* theme)
{
	current_theme = theme;
}

void begin_panel(char const* panel_name, OrthographicCamera const& camera, FrameParams frame_params)
{
	ASSERT(!current_panel, "You cannot begin another panel while another panel is bound!");

	bool   panel_exists = false;
	size_t panel_index  = 0;
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

	glm::vec2& panel_position = current_panel->position;
	glm::vec2& panel_size     = current_panel->size;

	glm::vec2 mouse_position = Input::get_current_mouse_position();
	glm::vec2 delta          = mouse_position - panel_position;
	bool      is_clicked     = Input::is_mouse_button_pressed(Mouse::ButtonLeft);

	if(is_mouse_in_bounds(mouse_position, panel_position, panel_size)) {
		if(current_state == STATE_NONE) {
			if(mouse_position.x < panel_position.x + RESIZE_REGION_WIDTH)
				current_state |= STATE_RESIZE_LEFT;
			else if(mouse_position.x > (panel_position.x + panel_size.x - RESIZE_REGION_WIDTH))
				current_state |= STATE_RESIZE_RIGHT;

			if(mouse_position.y > (panel_position.y + panel_size.y - RESIZE_REGION_WIDTH))
				current_state |= STATE_RESIZE_BOTTOM;
		}

		if(mouse_position.y < panel_position.y + RESIZE_REGION_WIDTH && current_state == STATE_NONE)
			current_state |= STATE_DRAG;
	}

	if(is_clicked && (current_state == STATE_DRAG || is_drag_started)) {
		if(!is_drag_started) {
			is_drag_started = true;
			start_delta     = delta;
		}

		panel_position = mouse_position - (start_delta);
	} else if(is_clicked && current_state != STATE_NONE) {
		if(current_state & STATE_RESIZE_RIGHT) {
			panel_size.x = mouse_position.x - panel_position.x;
		}

		if(current_state & STATE_RESIZE_LEFT) {
			if(panel_size.x - delta.x > DEFAULT_PANEL_WIDTH) {
				panel_position.x += delta.x;
				panel_size.x     -= delta.x;
			} else {
				delta.x = panel_size.x - DEFAULT_PANEL_WIDTH;

				panel_position.x += delta.x;
				panel_size.x     -= delta.x;
			}
		}

		if(current_state & STATE_RESIZE_BOTTOM) {
			panel_size.y = mouse_position.y - panel_position.y;
		}

		if(panel_size.x < DEFAULT_PANEL_WIDTH)
			panel_size.x = DEFAULT_PANEL_WIDTH;

		if(panel_size.y < DEFAULT_PANEL_HEIGHT)
			panel_size.y = DEFAULT_PANEL_HEIGHT;
	} else {
		current_state   = STATE_NONE;
		is_drag_started = false;
	}

	if(panel_position.x < 0)
		panel_position.x = 0.0f;
	if(panel_position.y < 0)
		panel_position.y = 0.0f;

	UIRenderer::begin(camera);
	UIRenderer::fill_rect(current_panel->position
	                    , current_panel->size
	                    , { 0.4f, 0.4f, 0.4f, 1.0f });
}

void end_panel()
{
	UIRenderer::end();

	current_panel = nullptr;
}

bool button(char const* label) { return false; }

}
