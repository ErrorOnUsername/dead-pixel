#include "Window.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace DP {

Window::Window(int32_t width, int32_t height, bool fullscreen)
	: m_width(width)
	, m_height(height)
	, m_fullscreen(fullscreen)
{ }

Window::~Window()
{ }

int Window::initialize()
{
	if (!glfwInit())
		return -1;

	m_window = glfwCreateWindow(m_width, m_height, "Dead Pixel Test", nullptr, nullptr);

	if (!m_window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSwapInterval(1);

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		return -1;
	}
	glViewport(0, 0, m_width, m_height);

	return 0;
}

}