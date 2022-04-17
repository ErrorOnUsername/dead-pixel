#include <gfx/renderer.hh>

#include <glad/glad.h>

namespace DP::Renderer {

void clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void set_clear_color(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

}
