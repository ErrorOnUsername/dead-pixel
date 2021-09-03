#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <Core/Log.h>
#include <Core/Window.h>
#include <Renderer/Renderer.h>

int main()
{
	DP::Window window;

	int initialize_return = window.initialize();
	if(initialize_return != 0)
		return initialize_return;

	DP::Renderer::set_clear_color(1.0f, 0.0f, 1.0f);

	DP::Log::init();

	DP_INFO("Starting DeadPixel...");

	while(!window.should_close())
	{
		DP::Renderer::clear();

		/* TODO: Update layers */

		window.swap_buffers();
		window.poll_events();
	}
	glfwTerminate();
}
