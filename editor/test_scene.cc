#include "test_scene.hh"

#include <glm/gtc/matrix_transform.hpp>

#include <gfx/buffer.hh>
#include <gfx/renderer.hh>

TestScene::TestScene()
	: DP::Scene("TestScene")
	, cube_va(DP::VertexArray::create())
{
	// HACK: None of this stuff should be here obvi. we should make geometry in the UI, using the ECS

	float vertices[7 * 4 * 6] = {
		// BACK
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f,

		// FRONT
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,

		// LEFT
		-0.5f, -0.5f, -0.5f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, -1.0f, 0.0f, 0.0f,

		// RIGHT
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f,

		// TOP
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f,

		// BOTTOM
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, -1.0f, 0.0f
	};

	uint32_t indices[6 * 6] = {
		0,  1,  2,  2,  3,  0,
		4,  5,  6,  6,  7,  4,
		8,  9,  10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20,
	};

	auto cube_vb = DP::VertexBuffer::create(vertices, sizeof(vertices));

	DP::BufferLayout buffer_layout = {
		{ DP::ShaderDataType::Float3, "in_position" },
		{ DP::ShaderDataType::Float,  "in_color"    },
		{ DP::ShaderDataType::Float3, "in_normal"   },
	};

	cube_vb->buffer_layout = buffer_layout;
	cube_va->add_vertex_buffer(cube_vb);

	auto cube_ib= DP::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));
	cube_va->set_index_buffer(cube_ib);

	cube_shader = DP::Shader::create("editor/shaders/basic_cube.vert" , "editor/shaders/basic_cube.frag");
}

static float rotation = 0.0f;
void TestScene::on_update_editor(float delta_time, DP::Camera* editor_camera)
{
	cube_shader->bind();
	cube_shader->set_uniform_mat4("u_pv_matrix", editor_camera->pv_matrix);
	cube_shader->set_uniform_mat4("u_transform_matrix", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f)) * glm::rotate(glm::mat4(1.0f), rotation, {0.0, 1.0, 1.0}));

	DP::Renderer::submit_draw(cube_va);

	rotation += 0.03f;
}

void TestScene::on_update_runtime(float delta_time)
{}
