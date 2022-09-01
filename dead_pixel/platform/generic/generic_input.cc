#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <core/application.hh>
#include <core/input.hh>

namespace DP::Input {

bool is_key_down(KeyCode key)
{
	auto* window = (GLFWwindow*)Application::current_window()->window_handle;
	auto state = glfwGetKey(window, (int32_t)key);
	return state == GLFW_PRESS;
}

bool is_mouse_button_down(MouseCode mouse_button)
{
	auto* window = (GLFWwindow*)Application::current_window()->window_handle;
	auto state = glfwGetMouseButton(window, (int32_t)mouse_button);
	return state == GLFW_PRESS;
}

glm::vec2 mouse_position()
{
	auto* window = (GLFWwindow*)Application::current_window()->window_handle;
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return { (float)x, (float)y };
}

}
