#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <Renderer/API/GraphicsContext.h>
namespace DP {
class GLContext : public GraphicsContext {
public:
	GLContext(GLFWwindow* window);

	void init() override;
	void swap_buffers() override;

private:
	GLFWwindow* m_window;
};
}