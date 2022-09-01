#include "editor_layer.hh"
#include "gfx/shader.hh"

#include <imgui.h>

#include <core/application.hh>
#include <core/assert.hh>
#include <entity_system/components/bitmasks.hh>
#include <gfx/renderer.hh>
#include <gfx/framebuffer.hh>
#include <panels.hh>

static float grid_plane_vertices[] = {
	-5.0f,  0.0f, -5.0f, 0.0f, 1.0f, 0.0f,
	 5.0f,  0.0f, -5.0f, 0.0f, 1.0f, 0.0f,
	 5.0f,  0.0f,  5.0f, 0.0f, 1.0f, 0.0f,
	-5.0f,  0.0f,  5.0f, 0.0f, 1.0f, 0.0f,
};

static uint32_t grid_plane_indices[] = {
	0,  1,  2,  2,  3,  0,
};

static float vertices[7 * 4 * 6] = {
	// BACK
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

	// FRONT
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

	// LEFT
	-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,

	// RIGHT
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

	// BOTTOM
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,

	// TOP
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
};

static uint32_t indices[] = {
	0,  1,  2,  2,  3,  0,
	4,  5,  6,  6,  7,  4,
	8,  9,  10, 10, 11, 8,
	12, 13, 14, 14, 15, 12,
	16, 17, 18, 18, 19, 16,
	20, 21, 22, 22, 23, 20,
};

void EditorLayer::on_attach()
{
	DP::FramebufferFormat fmt = {
		.width = 1280,
		.height = 720,
		.samples = 1,
		.attachments = { DP::FramebufferTextureFormat::RGBA8, DP::FramebufferTextureFormat::Depth }
	};

	framebuffer = new DP::Framebuffer(fmt);

	auto* window  = DP::Application::current_window();
	editor_camera = new DP::EditorCamera(45.0f, (float)window->data.width / (float)window->data.height, 0.1f, 1000.0f);

	grid_plane_va = new DP::VertexArray();

	auto* grid_plane_vb = new DP::VertexBuffer(grid_plane_vertices, sizeof(grid_plane_vertices));
	grid_plane_vb->buffer_layout = DP::BufferLayout {
		{ DP::ShaderDataType::Float3, "in_position" },
		{ DP::ShaderDataType::Float3, "in_normal" }
	};

	auto* grid_plane_ib = new DP::IndexBuffer(grid_plane_indices, sizeof(grid_plane_indices) / sizeof(u32));

	grid_plane_va->add_vertex_buffer(grid_plane_vb);
	grid_plane_va->set_index_buffer(grid_plane_ib);

	grid_plane_shader = new DP::Shader("editor/assets/shaders/grid.vert", "editor/assets/shaders/grid.frag");

	test_scene = new DP::Scene("Test");

	auto* e = test_scene->data->context.request_new("Cube");

	e->mesh.set_data(vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(u32));
	e->component_bitfield = DP::Component::TRANSFORM_COMPONENT_BITMASK | DP::Component::MESH_COMPONENT_BITMASK;
}

void EditorLayer::on_update(float delta_time)
{
	DP::FramebufferFormat fmt = framebuffer->format;
	if(current_viewport_size.x > 0.0f && current_viewport_size.y > 0.0f &&
	   (fmt.width != current_viewport_size.x || fmt.height != current_viewport_size.y))
	{
		framebuffer->resize(current_viewport_size.x, current_viewport_size.y);
	}

	framebuffer->bind();
	DP::Renderer::set_clear_color(0.3f, 0.3f, 0.3f);
	DP::Renderer::clear();

	test_scene->on_update_editor(delta_time, editor_camera);

	auto t = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	DP::Renderer::begin_draw_scope(editor_camera);
	DP::Renderer::submit_draw(grid_plane_shader, grid_plane_va, t);
	DP::Renderer::end_draw_scope();


	framebuffer->unbind();
}

void EditorLayer::on_imgui_render()
{
	bool is_dockspace_open = true;
	bool is_fullscreen = true;

	ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
#ifndef __APPLE__
	window_flags |= ImGuiWindowFlags_MenuBar;
#endif

	if(is_fullscreen) {
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
		                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		                ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	if(dock_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
	ImGui::Begin("Editor Dockspace", &is_dockspace_open, window_flags);
	ImGui::PopStyleVar();

	if(is_fullscreen)
		ImGui::PopStyleVar(2);

	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();

	float prev_min_width = style.WindowMinSize.x;
	style.WindowMinSize.x = 315.0f;

	if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
		ImGuiID dock_id = ImGui::GetID("DeadPixelDockSpace");
		ImGui::DockSpace(dock_id, {0.0f, 0.0f}, dock_flags);
	}

	style.WindowMinSize.x = prev_min_width;

	// FIXME: We should use apple APIs for this on mac, since they
	//        dont use the same window style as linux and windows
#ifndef __APPLE__
	if(ImGui::BeginMenuBar()) {
		if(ImGui::BeginMenu("File")) {
			if(ImGui::MenuItem("New Scene", "Ctrl+N")) { }
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
#endif

	draw_scene_panel(dynamic_cast<DP::Scene*>(test_scene));
	draw_property_panel(dynamic_cast<DP::Scene*>(test_scene));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
	ImGui::Begin("Viewport");

	auto viewport_min_size = ImGui::GetWindowContentRegionMin();
	auto viewport_max_size = ImGui::GetWindowContentRegionMax();
	auto viewport_offset   = ImGui::GetWindowPos();

	viewport_minimum_bounds = { viewport_offset.x + viewport_min_size.x, viewport_offset.y + viewport_min_size.y };
	viewport_maximum_bounds = { viewport_offset.x + viewport_max_size.x, viewport_offset.y + viewport_max_size.y };
	auto viewport_panel_size = ImGui::GetContentRegionAvail();
	current_viewport_size = { viewport_panel_size.x, viewport_panel_size.y };

	editor_camera->adjust_aspect_ratio(current_viewport_size.x / current_viewport_size.y);

	u64 texture_id = framebuffer->attachment_id(0);
	ImGui::Image((void*)texture_id, { current_viewport_size.x, current_viewport_size.y }, { 0.0f, 1.0f }, { 1.0f, 0.0f });

	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::End();
}

void EditorLayer::on_event(DP::Event& e)
{
	editor_camera->on_event(e);
}
