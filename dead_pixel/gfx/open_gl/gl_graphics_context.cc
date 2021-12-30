#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <core/assert.hh>
#include <core/log.hh>
#include <gfx/graphics_context.hh>

namespace DP {

GraphicsContext::GraphicsContext(void* window)
{
	ASSERT(window, "Window handle was null!!");

	window_handle = window;

	glfwMakeContextCurrent((GLFWwindow*)window_handle);

	int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	ASSERT(result, "Failed to initialize GLAD!!");

	DP_ENGINE_INFO("OpenGL Info:");
	DP_ENGINE_INFO("    Vendor:   {0}", glGetString(GL_VENDOR));
	DP_ENGINE_INFO("    Version:  {0}", glGetString(GL_VERSION));
	DP_ENGINE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void GraphicsContext::swap_buffers()
{
	glfwSwapBuffers((GLFWwindow*)window_handle);
}

}
