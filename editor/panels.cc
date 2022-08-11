#include "panels.hh"

#include <imgui.h>
#include <imgui_internal.h>
#include <glm/glm.hpp>

#include <entity_system/entity.hh>
#include <entity_system/components/bitmasks.hh>
#include <entity_system/components/mesh_component.hh>
#include <entity_system/components/transform_component.hh>

static u32 selected_id = 0;

static void draw_transform_widget(DP::TransformComponent&);
static void draw_mesh_widget(DP::MeshComponent&);

void draw_scene_panel(DP::Scene* scene)
{
	if(ImGui::Begin("Scene Hierarchy")) {
		if(ImGui::Button("New Entity")) {
			DP::Entity* e = scene->data->context.request_new("Empty Entity");
			e->component_bitfield = DP::Component::TRANSFORM_COMPONENT_BITMASK;
		}

		ImGuiTreeNodeFlags root_flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth;
		if(ImGui::TreeNodeEx("SCENE", root_flags, "%s", scene->name)) {
			scene->data->context.for_each([] (DP::Entity* entity) {
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanAvailWidth;

				if(entity->id == selected_id)
					flags |= ImGuiTreeNodeFlags_Selected;

				if(ImGui::TreeNodeEx("ENTITY", flags, "%s", entity->name)) {
					if(ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
						selected_id = entity->id;
					else if(!ImGui::IsAnyItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
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
			if(components & DP::Component::TRANSFORM_COMPONENT_BITMASK)
				draw_transform_widget(entity->transform);
			if (components & DP::Component::MESH_COMPONENT_BITMASK)
				draw_mesh_widget(entity->mesh);
		} else {
			ImGui::Text("No entity selected...");
		}
	}
	ImGui::End();
}

static void draw_vec3_control(char const* label, glm::vec3& vector, glm::vec3 reset_vec);

static void draw_transform_widget(DP::TransformComponent& transform)
{
	ImGui::Separator();
	ImGui::Spacing();

	ImGui::Text("Transform");
	draw_vec3_control("Positon", transform.positon, glm::vec3(0, 0, 0));
	draw_vec3_control("Rotation", transform.rotation, glm::vec3(0, 0, 0));
	draw_vec3_control("Scale", transform.scale, glm::vec3(1, 1, 1));

	ImGui::Spacing();
	ImGui::Separator();
}

static void draw_mesh_widget(DP::MeshComponent& mesh)
{
	ImGui::Spacing();

	ImGui::Text("Mesh");

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 75.0f);

	ImGui::Text("File");
	ImGui::NextColumn();

	ImGui::Text("INSERT FILE PATH");

	ImGui::NextColumn();
	ImGui::Text("Vertices");
	ImGui::NextColumn();
	ImGui::Text("VERT COUNT");

	ImGui::NextColumn();
	ImGui::Text("Triangles");
	ImGui::NextColumn();
	ImGui::Text("TRI COUNT");

	ImGui::Columns(1);

	ImGui::Spacing();
	ImGui::Separator();
}

static void draw_vec3_control(char const* label, glm::vec3& vector, glm::vec3 reset_vec)
{
	ImGui::PushID(label);
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 75.0f);

	ImGui::Text("%s", label);
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });

	float  line_height = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 button_size = { line_height + 3.0f, line_height };

	//
	// X Component Control
	//

	ImGui::PushStyleColor(ImGuiCol_Button, { 0.5f, 0.1f, 0.1f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.6f, 0.2f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.5f, 0.1f, 0.1f, 1.0f });
	if(ImGui::Button("X", button_size))
		vector.x = reset_vec.x;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &vector.x, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	//
	// Y Component Control
	//

	ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.5f, 0.1f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.2f, 0.6f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.1f, 0.5f, 0.1f, 1.0f });
	if(ImGui::Button("Y", button_size))
		vector.y = reset_vec.y;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &vector.y, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	//
	// Z Component Control
	//

	ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.1f, 0.5f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.2f, 0.2f, 0.6f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.1f, 0.1f, 0.5f, 1.0f });
	if(ImGui::Button("Z", button_size))
		vector.z = reset_vec.z;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Z", &vector.z, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();

	ImGui::Columns(1);
	ImGui::PopID();
}
