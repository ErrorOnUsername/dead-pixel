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
	ImGui::ShowDemoWindow();
}

void EditorLayer::on_event(DP::Event& e) { }
