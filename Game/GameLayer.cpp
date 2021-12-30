#include "GameLayer.h"

#include <glm/gtc/matrix_transform.hpp>

GameLayer::GameLayer()
	: Layer("GameLayer")
	, m_camera(1280.0f / 1024.0f)
	, m_cube_transform(1.0f)
	, m_cube_rotation(0.0f)
{
	m_vertex_array = DP::make_ref_ptr<DP::VertexArray>();

	float vertices[3*4*6] = {
		// BACK
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,

		// FRONT
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		// LEFT
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,

		// RIGHT
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,

		// TOP
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,

		// BOTTOM
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f
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
	};
	vertex_buffer->buffer_layout = buffer_layout;
	m_vertex_array->add_vertex_buffer(vertex_buffer);

	DP::RefPtr<DP::IndexBuffer> index_buffer = DP::make_ref_ptr<DP::IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));
	m_vertex_array->set_index_buffer(index_buffer);

	char const* vert_src = R"(
		#version 400 core

		layout(location = 0) in vec3 in_position;

		out vec3 pass_color;

		uniform mat4 u_pv_matrix;
		uniform mat4 u_transform_matrix;

		void main()
		{
			pass_color = in_position + 0.5f;
			gl_Position = u_pv_matrix * u_transform_matrix * vec4(in_position, 1.0);
		}
	)";

	char const* frag_src = R"(
		#version 400 core

		in vec3 pass_color;

		out vec4 out_color;

		void main()
		{
			out_color = vec4(pass_color, 1.0);
		}
	)";

	m_shader = DP::make_ref_ptr<DP::Shader>("test_shader", vert_src, frag_src);
	m_shader->bind();

	m_cube_transform = glm::translate(glm::mat4(1.0f), {0.0f, 0.0f, -2.0f});
}

void GameLayer::on_update(float delta_time)
{
	DP::Renderer::set_clear_color(0.0f, 0.0f, 0.0f, 1.0f);
	DP::Renderer::clear();

	m_cube_transform = glm::rotate(m_cube_transform, 1.0f * delta_time, {1.0, 0.0f, 1.0f});

	m_shader->set_uniform_mat4("u_pv_matrix", m_camera.pv_matrix);
	m_shader->set_uniform_mat4("u_transform_matrix", m_cube_transform);


	DP::Renderer::draw_indexed(m_vertex_array);
}

void GameLayer::on_event(DP::Event& e) { }
