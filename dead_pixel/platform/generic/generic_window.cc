#include <core/window.hh>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <core/assert.hh>
#include <core/log.hh>
#include <core/types.hh>
#include <gfx/graphics_context.hh>

namespace DP {

static void glfw_error_callback(int error, char const* description)
{
	ASSERT_FMT(false, "GLFW error: {}", description);
}

Window::Window(char const* title, u32 width, u32 height)
{
	ASSERT(glfwInit(), "Failed to initialize GLFW");

	data.width  = width;
	data.height = height;

#ifdef __APPLE__
	// Workaround for macOS
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	window_handle = (void*)glfwCreateWindow(width, height, title, nullptr, nullptr);
	DP_ENGINE_INFO("Created window: {} ({}x{})", title, width, height);

	GraphicsContext::init(window_handle);

	enable_vsync(true);

	glViewport(0, 0, width, height);

	glfwSetWindowUserPointer((GLFWwindow*)window_handle, &data);

	glfwSetWindowSizeCallback((GLFWwindow*)window_handle, [] (GLFWwindow* window, int width, int height) {
		auto* data = (WindowData*)glfwGetWindowUserPointer(window);

		data->width  = width;
		data->height = height;

		WindowResizedEvent event(width, height);
		data->event_callback(event);
	});

	glfwSetWindowCloseCallback((GLFWwindow*)window_handle, [] (GLFWwindow* window) {
		auto* data = (WindowData*)glfwGetWindowUserPointer(window);

		WindowClosedEvent event;
		data->event_callback(event);
	});

	glfwSetKeyCallback((GLFWwindow*)window_handle, [] (GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto* data = (WindowData*)glfwGetWindowUserPointer(window);

		switch(action) {
			case GLFW_PRESS: {
				KeyPressedEvent event(key, false);
				data->event_callback(event);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent event(key);
				data->event_callback(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent event(key, true);
				data->event_callback(event);
				break;
			}
		}
	});

	glfwSetMouseButtonCallback((GLFWwindow*)window_handle, [] (GLFWwindow* window, int button, int action, int mods) {
		auto* data = (WindowData*)glfwGetWindowUserPointer(window);

		switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent e(button);
				data->event_callback(e);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent e(button);
				data->event_callback(e);
				break;
			}
		}
	});

	glfwSetScrollCallback((GLFWwindow*)window_handle, [] (GLFWwindow* window, double x_offset, double y_offset) {
		auto* data = (WindowData*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event(x_offset, y_offset);
		data->event_callback(event);
	});

	glfwSetCursorPosCallback((GLFWwindow*)window_handle, [] (GLFWwindow* window, double x_position, double y_position) {
		auto* data = (WindowData*)glfwGetWindowUserPointer(window);

		MouseMovedEvent event(x_position, y_position);
		data->event_callback(event);
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
