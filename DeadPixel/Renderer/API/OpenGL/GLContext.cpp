#include "GLContext.h"
#include <iostream>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace DP {
GLContext::GLContext(GLFWwindow* window)
	: m_window(window)
{ }

void GLContext::init()
{
	glfwMakeContextCurrent(m_window);
	int32_t status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if(status != 0)
	{
		std::cout << "Failed to initialize glad!" << std::endl;
		exit(status);
	}
}

void GLContext::swap_buffers()
{
	glfwSwapBuffers(m_window);
}
}