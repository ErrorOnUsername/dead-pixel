#include "editor_layer.hh"

#include <imgui.h>

#include <gfx/renderer.hh>

void EditorLayer::on_attach()
{
	DP::Renderer::set_clear_color(0.3f, 0.3f, 0.3f);
}

void EditorLayer::on_update(float delta_time)
{
	DP::Renderer::clear();
}

void EditorLayer::on_imgui_render()
{
	bool is_dockspace_open = true;
	bool is_fullscreen = true;

	ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

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

	if(ImGui::BeginMenuBar()) {
		if(ImGui::BeginMenu("File")) {
#ifdef __APPLE__
			// FIXME: We should use apple APIs for this on mac, since they
			//        dont use the same window style as linux and windows
			if(ImGui::MenuItem("New Scene", "Cmd+N")) { }
#else
			if(ImGui::MenuItem("New Scene", "Ctrl+N")) { }
#endif
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::End();
}

void EditorLayer::on_event(DP::Event& e) { }
