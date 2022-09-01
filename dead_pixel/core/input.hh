#pragma once

#include <core/input_codes.hh>

#include <glm/glm.hpp>

namespace DP::Input {

bool is_key_down(KeyCode);
bool is_mouse_button_down(MouseCode);

glm::vec2 mouse_position();

}
