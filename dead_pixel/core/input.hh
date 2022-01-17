#pragma once

#include <glm/glm.hpp>

#include <core/keycode.hh>
#include <core/mouse_code.hh>

namespace DP::Input {

bool is_key_pressed(KeyCode);
bool is_mouse_button_pressed(MouseCode);

glm::vec2 get_current_mouse_position();

}
