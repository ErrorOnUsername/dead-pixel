#include "panels.hh"

#include <imgui.h>

#include <entity_system/components/bitmasks.hh>

static u32 selected_id = 0;

void draw_scene_panel(DP::Scene* scene)
{
	if(ImGui::Begin("Scene Hierarchy")) {
		if(ImGui::TreeNode(scene->name)) {
			scene->data->context.for_each([] (DP::Entity* entity) {
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;

				if(entity->id == selected_id)
					flags |= ImGuiTreeNodeFlags_Selected;

				if(ImGui::TreeNodeEx("ENTITY", flags, "%s", entity->name)) {
					if(ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
						selected_id = entity->id;
					else if(ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsItemClicked())
						selected_id = 0;
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
		DP::Entity* entity = scene->data->context.from_id(selected_id);
		if(entity) {
			ImGui::Text("Selected Entity: %s", entity->name);

			u32 components = entity->component_bitfield;
			if(components & DP::Component::TRANSFORM_COMPONENT_BITMASK) {
				ImGui::TextColored({ 1.0f, 0.0f, 0.0f, 1.0f }, "Transform");
			}
			if (components & DP::Component::MESH_COMPONENT_BITMASK) {
				ImGui::TextColored({ 0.0f, 1.0f, 0.0f, 1.0f }, "Mesh");
			}
		} else {
			ImGui::Text("No entity selected...");
		}
	}
	ImGui::End();
}
