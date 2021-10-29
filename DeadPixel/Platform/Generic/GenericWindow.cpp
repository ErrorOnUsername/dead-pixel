#include "GenericWindow.h"

#include <dppch.h>
#include <Core/Assert.h>
#include <Core/Window.h>
#include <Events/ApplicationEvent.h>
#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>

namespace DP {

Window* Window::create(WindowProperties const& properties)
{
	return new GenericWindow(properties);
}

static bool s_is_glfw_initialized = false;

static void glfw_error_callback(int error, char const* description)
{
	DP_ENGINE_ERROR("GLFW Error [{0}]: {1}", error, description);
}

GenericWindow::GenericWindow(WindowProperties const& properties)
{
	DP_ENGINE_INFO("Creating window {0} ({1} X {2})",
	               properties.title,
	               properties.width,
	               properties.height);

	m_data.title = properties.title;
	m_data.width = properties.width;
	m_data.height = properties.height;

	if(!s_is_glfw_initialized) {
		int init_status = glfwInit();
		ASSERT(init_status, "Failed to initialize GLFW!!!");

		s_is_glfw_initialized = true;
	}

	m_window = glfwCreateWindow((int)properties.width,
	                            (int)properties.height,
	                            properties.title,
	                            nullptr,
	                            nullptr);
	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, &m_data);
	set_is_vsync_enabled(true);

	glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		data->width = width;
		data->height = height;

		WindowResizeEvent e(width, height);
		data->event_callback(e);
	});

	glfwSetWindowCloseCallback(m_window, [] (GLFWwindow* window) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent e;
		data->event_callback(e);
	});

	glfwSetKeyCallback(m_window, [] (GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

		switch(action) {
			case GLFW_PRESS: {
				KeyPressedEvent e(key, 0);
				data->event_callback(e);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent e(key);
				data->event_callback(e);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent e(key, 1);
				data->event_callback(e);
				break;
			}
		}
	});

	glfwSetMouseButtonCallback(m_window, [] (GLFWwindow* window, int button, int action, int mods) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

		switch(action) {
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

	glfwSetScrollCallback(m_window, [] (GLFWwindow* window, double x_offset, double y_offset) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		MouseScrolledEvent e((float)x_offset, (float)y_offset);
		data->event_callback(e);
	});

	glfwSetCursorPosCallback(m_window, [] (GLFWwindow* window, double x_position, double y_position) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		MouseMovedEvent e(x_position, y_position);
		data->event_callback(e);
	});

	glfwSetErrorCallback(glfw_error_callback);
}

GenericWindow::~GenericWindow()
{
	glfwDestroyWindow(m_window);
}

void GenericWindow::on_update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

void GenericWindow::set_is_vsync_enabled(bool enabled)
{
	if(enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_data.is_vsync_enabled = enabled;
}

}
