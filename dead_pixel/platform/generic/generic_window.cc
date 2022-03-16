#include <core/window.hh>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <core/assert.hh>
#include <core/types.hh>
#include <gfx/graphics_context.hh>

namespace DP {

static void glfw_error_callback(int error, char const* description)
{
	ASSERT(false);
}

Window::Window(char const* title, u32 width, u32 height)
{
	ASSERT(glfwInit());

	data.width  = width;
	data.height = height;

#ifdef __APPLE__
	// Workaround for macOS
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	window_handle = (void*)glfwCreateWindow(width, height, title, nullptr, nullptr);

	GraphicsContext::init(window_handle);

	enable_vsync(true);

	glfwSetWindowUserPointer((GLFWwindow*)window_handle, &data);

	glfwSetWindowSizeCallback((GLFWwindow*)window_handle, [] (GLFWwindow* window, int width, int height) {
		auto* data = (WindowData*)glfwGetWindowUserPointer(window);

		data->width  = width;
		data->height = height;

		// TODO: Propagate event
	});

	glfwSetWindowCloseCallback((GLFWwindow*)window_handle, [] (GLFWwindow* window) {
		// TODO: Propagate event
	});

	glfwSetKeyCallback((GLFWwindow*)window_handle, [] (GLFWwindow* window, int key, int scancode, int action, int mods) {
		switch(action) {
			case GLFW_PRESS: {
				// TODO: Propagate event
				break;
			}
			case GLFW_RELEASE: {
				// TODO: Propagate event
				break;
			}
			case GLFW_REPEAT: {
				// TODO: Propagate event
				break;
			}
		}
	});

	glfwSetScrollCallback((GLFWwindow*)window_handle, [] (GLFWwindow* window, double x_offset, double y_offset) {
		// TODO: Propagate event
	});

	glfwSetCursorPosCallback((GLFWwindow*)window_handle, [] (GLFWwindow* window, double x_position, double y_position) {
		// TODO: Propagate event
	});
}

Window::~Window()
{
	glfwDestroyWindow((GLFWwindow*)window_handle);
}

void Window::on_update()
{
	glfwPollEvents();
	GraphicsContext::swap_buffers(window_handle);
}

void Window::set_title(char const* title)
{
	glfwSetWindowTitle((GLFWwindow*)window_handle, title);
}

void Window::set_dimensions(u32 width, u32 height)
{
	glfwSetWindowSize((GLFWwindow*)window_handle, width, height);

	data.width  = width;
	data.height = height;
}

void Window::enable_vsync(bool enabled)
{
	glfwSwapInterval((enabled) ? 1 : 0);

	data.vsync_enabled = enabled;
}

bool Window::should_close()
{
	return glfwWindowShouldClose((GLFWwindow*)window_handle);
}

}
