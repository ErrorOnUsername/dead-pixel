#pragma once

#include <cstdint>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace DP {
class Window {
public:
	Window(int32_t width = 1024, int32_t height = 576, bool fullscreen = false);
	~Window();

	int initialize();

	void swap_buffers() { glfwSwapBuffers(m_window); }
	void poll_events() { glfwPollEvents(); }

	bool is_fullscreen() { return m_fullscreen; }
	void set_fullscreen(bool value) { m_fullscreen = value; }

	bool should_close() { return glfwWindowShouldClose(m_window); }
	void set_should_close(bool value) { glfwSetWindowShouldClose(m_window, value); }

	GLFWwindow* window() { return m_window; }

private:
	GLFWwindow* m_window;

	int32_t m_width;
	int32_t m_height;

	bool m_fullscreen;
	bool m_should_close;
};
}
