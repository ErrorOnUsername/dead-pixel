#include <gfx/graphics_context.hh>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <core/assert.hh>

namespace DP::GraphicsContext {

void init(void* window_handle)
{
	glfwMakeContextCurrent((GLFWwindow*)window_handle);

	ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
}

void swap_buffers(void* window_handle)
{
	glfwSwapBuffers((GLFWwindow*)window_handle);
}

}
