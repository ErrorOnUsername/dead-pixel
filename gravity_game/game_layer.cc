#include "game_layer.hh"

#include <glm/gtc/matrix_transform.hpp>

GameLayer::GameLayer()
	: Layer("GameLayer")
	, m_camera(1280.0f / 1024.0f)
	, m_ui_camera(0.0f, 1280.0f, 0.0f, 1024.0f)
	, m_cube_transform(1.0f)
	, m_cube_rotation(0.0f)
{
	m_vertex_array = DP::make_ref_ptr<DP::VertexArray>();

	float vertices[4*4*6] = {
		// BACK
		-0.5f, -0.5f, -0.5f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f,

		// FRONT
		-0.5f, -0.5f,  0.5f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f,

		// LEFT
		-0.5f, -0.5f, -0.5f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f,

		// RIGHT
		 0.5f, -0.5f,  0.5f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f,

		// TOP
		-0.5f,  0.5f,  0.5f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f,

		// BOTTOM
		-0.5f, -0.5f, -0.5f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f
	};

	uint32_t indices[6*6] = {
		0,  1,  2,  2,  3,  0,
		4,  5,  6,  6,  7,  4,
		8,  9,  10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20,
	};

	DP::RefPtr<DP::VertexBuffer> vertex_buffer = DP::make_ref_ptr<DP::VertexBuffer>(vertices, sizeof(vertices));
	DP::BufferLayout buffer_layout = {
		{ DP::ShaderDataType::Float3, "in_position" },
		{ DP::ShaderDataType::Float,  "in_color" },
	};
	vertex_buffer->buffer_layout = buffer_layout;
	m_vertex_array->add_vertex_buffer(vertex_buffer);

	DP::RefPtr<DP::IndexBuffer> index_buffer = DP::make_ref_ptr<DP::IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));
	m_vertex_array->set_index_buffer(index_buffer);

	m_shader = DP::make_ref_ptr<DP::Shader>("gravity_game/assets/shaders/basic_cube.vert"
	                                      , "gravity_game/assets/shaders/basic_cube.frag");

	DP::UI::UIRenderer::init();

	DP::Renderer::set_clear_color(0.0f, 0.0f, 0.0f, 1.0f);
}

void GameLayer::on_update(float delta_time)
{
	DP::Renderer::clear();
	m_cube_transform = glm::translate(glm::mat4(1.0f), {0.0f, 0.0f, -5.0f});
	m_cube_transform = glm::rotate(m_cube_transform, m_cube_rotation, {1.0f, 1.0f, 0.0f});

	m_shader->bind();
	m_shader->set_uniform_mat4("u_pv_matrix", m_camera.pv_matrix);
	m_shader->set_uniform_mat4("u_transform_matrix", m_cube_transform);

	DP::Renderer::draw_indexed(m_vertex_array);

	DP::UI::UIRenderer::begin(m_ui_camera);
	DP::UI::UIRenderer::fill_rect({300.0f, 300.0f, 0.0f}, {100.0f, 200.0f}, {0.9f, 0.2f, 0.2f, 1.0f});
	DP::UI::UIRenderer::fill_rect({400.0f, 500.0f, 0.0f}, {220.0f, 170.0f}, {0.4f, 1.0f, 1.0f, 1.0f});
	DP::UI::UIRenderer::end();

	m_cube_rotation += 1.0f * delta_time;
}

void GameLayer::on_event(DP::Event& e) { }
