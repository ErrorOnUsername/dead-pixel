#include <glad/glad.h>

#include <GFX/Renderer.h>

namespace DP {

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::set_clear_color(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::enable_depth()
{
	glEnable(GL_DEPTH_TEST);
}

void Renderer::disable_depth()
{
	glDisable(GL_DEPTH_TEST);
}

void Renderer::draw_indexed(RefPtr<VertexArray> const& vertex_array)
{
	glDrawElements(GL_TRIANGLES, vertex_array->index_buffer->count, GL_UNSIGNED_INT, 0);
}

}
