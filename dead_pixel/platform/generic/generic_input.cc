#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <core/application.hh>
#include <core/input.hh>

namespace DP::Input {

bool is_key_pressed(KeyCode keycode)
{
	GLFWwindow* window = (GLFWwindow*)Application::current_window;
	int state = glfwGetKey(window, keycode);
	return (state == GLFW_PRESS || state == GLFW_REPEAT);
}

bool is_mouse_button_pressed(MouseCode mouse_code)
{
	GLFWwindow* window = (GLFWwindow*)Application::current_window;
	int state = glfwGetMouseButton(window, mouse_code);
	return state == GLFW_PRESS;
}

glm::vec2 get_current_mouse_position()
{
	GLFWwindow* window = (GLFWwindow*)Application::current_window;
	double x = 0.0;
	double y = 0.0;

	glfwGetCursorPos(window, &x, &y);
	return { (float)x, (float)y };
}

}
