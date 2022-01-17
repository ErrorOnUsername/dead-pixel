#include "ui_renderer.hh"

#include <glm/gtc/matrix_transform.hpp>

#include <core/memory.hh>
#include <gfx/buffer.hh>
#include <gfx/renderer.hh>
#include <gfx/shader.hh>
#include <gfx/vertex_array.hh>

namespace DP::UI {

struct Vertex {
	glm::vec4 position;
	glm::vec4 color;
};

static constexpr size_t QUAD_VERTEX_COUNT = 4;

static constexpr uint32_t MAX_QUAD_COUNT   = 100;
static constexpr uint32_t MAX_VERTEX_COUNT = MAX_QUAD_COUNT * QUAD_VERTEX_COUNT;
static constexpr uint32_t MAX_INDEX_COUNT  = MAX_QUAD_COUNT * 6;

glm::vec4 quad_vertices[4] = {
	{ 0.0f, 0.0f, 0.0f, 1.0f },
	{ 1.0f, 0.0f, 0.0f, 1.0f },
	{ 1.0f, 1.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 0.0f, 1.0f }
};

RefPtr<VertexArray>  vertex_array;
RefPtr<VertexBuffer> vertex_buffer;
RefPtr<IndexBuffer>  index_buffer;
RefPtr<Shader>       shader;

Vertex*  temp_vertices       = nullptr;
Vertex*  current_vertex      = nullptr;
uint32_t running_index_count = 0;

void UIRenderer::init()
{
	vertex_array = make_ref_ptr<VertexArray>();

	vertex_buffer = make_ref_ptr<VertexBuffer>(MAX_VERTEX_COUNT * sizeof(Vertex));
	vertex_buffer->buffer_layout = {
		{ ShaderDataType::Float4, "in_position" },
		{ ShaderDataType::Float4, "in_color"    }
	};
	vertex_array->add_vertex_buffer(vertex_buffer);

	temp_vertices = new Vertex[MAX_VERTEX_COUNT];

	uint32_t* indices = new uint32_t[MAX_INDEX_COUNT];

	uint32_t offset = 0;
	for(size_t i = 0; i < MAX_INDEX_COUNT; i += 6) {
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;
		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	RefPtr<IndexBuffer> index_buffer = make_ref_ptr<IndexBuffer>(indices, MAX_INDEX_COUNT);
	vertex_array->set_index_buffer(index_buffer);

	delete[] indices;

	shader = make_ref_ptr<Shader>("dead_pixel/gfx/ui/ui_default.vert"
	                            , "dead_pixel/gfx/ui/ui_default.frag");
}

void UIRenderer::shutdown()
{
	delete[] temp_vertices;
}

void UIRenderer::begin(OrthographicCamera const& camera)
{
	shader->bind();
	shader->set_uniform_mat4("u_pv_matrix", camera.pv_matrix);

	begin_next_batch();
}

void UIRenderer::begin_next_batch()
{
	running_index_count = 0;
	current_vertex = temp_vertices;
}

void UIRenderer::next_batch()
{
	flush();
	begin_next_batch();
}

void UIRenderer::end()
{
	flush();
}

void UIRenderer::flush()
{
	if(running_index_count == 0)
		return;

	uint32_t size = (uint8_t*)current_vertex - (uint8_t*)temp_vertices;
	vertex_buffer->set_data(temp_vertices, size);

	shader->bind();
	Renderer::draw_indexed(vertex_array, running_index_count);
}

void UIRenderer::fill_rect(glm::vec2 const& position, glm::vec2 const& size, glm::vec4 const& color)
{
	fill_rect({position.x, position.y, 0.0f}, size, color);
}

void UIRenderer::fill_rect(glm::vec3 const& position, glm::vec2 const& size, glm::vec4 const& color)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
	                    * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	fill_rect(transform, color);
}

void UIRenderer::fill_rect(glm::mat4 const& transfrom, glm::vec4 const& color)
{
	if(running_index_count >= MAX_INDEX_COUNT)
		next_batch();

	for(size_t i = 0; i < QUAD_VERTEX_COUNT; i++) {
		current_vertex->position = transfrom * quad_vertices[i];
		current_vertex->color    = color;
		current_vertex++;
	}

	running_index_count += 6;
}

}
