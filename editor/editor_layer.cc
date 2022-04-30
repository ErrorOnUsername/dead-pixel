#include "editor_layer.hh"

#include <imgui.h>

#include <core/assert.hh>
#include <gfx/renderer.hh>
#include <gfx/framebuffer.hh>

void EditorLayer::on_attach()
{
	DP::FramebufferFormat fmt = {
		.width = 1280,
		.height = 720,
		.samples = 1,
		.attachments = { DP::FramebufferTextureFormat::RGBA8, DP::FramebufferTextureFormat::Depth }
	};

	framebuffer = DP::Framebuffer::create(fmt);
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
	DP::Renderer::clear();
	DP::Renderer::set_clear_color(0.0f, 1.0f, 1.0f);
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

	float previous_min_width = style.WindowMinSize.x;
	style.WindowMinSize.x = 400.0f;

	if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
		ImGuiID dock_id = ImGui::GetID("DeadPixelDockSpace");
		ImGui::DockSpace(dock_id, {0.0f, 0.0f}, dock_flags);
	}

	style.WindowMinSize.x = previous_min_width;

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

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
	ImGui::Begin("Viewport");

	auto viewport_min_size = ImGui::GetWindowContentRegionMin();
	auto viewport_max_size = ImGui::GetWindowContentRegionMax();
	auto viewport_offset   = ImGui::GetWindowPos();

	viewport_minimum_bounds = { viewport_offset.x + viewport_min_size.x, viewport_offset.y + viewport_min_size.y };
	viewport_maximum_bounds = { viewport_offset.x + viewport_max_size.x, viewport_offset.y + viewport_max_size.y };
	auto viewport_panel_size = ImGui::GetContentRegionAvail();
	current_viewport_size = { viewport_panel_size.x, viewport_panel_size.y };

	u64 texture_id = framebuffer->attachment_id(0);
	ImGui::Image((void*)texture_id, { current_viewport_size.x, current_viewport_size.y });

	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::End();
}

void EditorLayer::on_event(DP::Event& e) { }
