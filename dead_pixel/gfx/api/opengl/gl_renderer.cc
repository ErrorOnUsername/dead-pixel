#include <gfx/renderer.hh>

#include <glad/glad.h>

namespace DP::Renderer {

static bool      in_draw_scope = false;
static glm::mat4 pv_matrix     = glm::mat4(1.0f);

void clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void set_clear_color(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

void begin_draw_scope(Camera* camera)
{
	pv_matrix = camera->pv_matrix;
	in_draw_scope = true;
}

void end_draw_scope()
{
	in_draw_scope = false;
}

void submit_draw(Shader* shader, VertexArray* vertex_array, glm::mat4 transform)
{
	ASSERT(in_draw_scope, "You must be in a draw scope to submit a draw call!");

	shader->bind();

	shader->set_uniform_mat4("u_pv_matrix", pv_matrix);
	shader->set_uniform_mat4("u_transform_matrix", transform);

	vertex_array->bind();
	glDrawElements(GL_TRIANGLES, vertex_array->index_buffer->count, GL_UNSIGNED_INT, 0);
	vertex_array->unbind();

	shader->unbind();
}

}
