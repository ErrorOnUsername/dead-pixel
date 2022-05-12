#include "panels.hh"
#include "imgui_internal.h"

#include <imgui.h>

static u32 selected_id = 0;

void draw_scene_panel(DP::Scene* scene)
{
	if(ImGui::Begin("Scene Hierarchy")) {
		if(ImGui::TreeNode(scene->name)) {
			scene->data->context.for_each([] (DP::Entity* entity) {
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
				if(entity->id == selected_id)
					flags |= ImGuiTreeNodeFlags_Selected;

				if(ImGui::TreeNodeEx("Entity", flags)) {
					if(ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
						selected_id = entity->id;
					ImGui::TreePop();
				}
			});

			ImGui::TreePop();
		}
	}
	ImGui::End();
}

void draw_property_panel(DP::Scene* scene)
{
	if(ImGui::Begin("Properties")) {
		ImGui::Text("Selected Entity: %d", selected_id);
	}
	ImGui::End();
}
