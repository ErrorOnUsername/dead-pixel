#include "scene.hh"

#include <entity_system/components/bitmasks.hh>
#include <gfx/renderer.hh>

namespace DP {

void Scene::on_update_editor(float delta_time, Camera *camera)
{
	Renderer::begin_draw_scope(camera);

	data->context.for_each([] (Entity* e) {
		if(e->component_bitfield & Component::MESH_COMPONENT_BITMASK &&
		   e->component_bitfield & Component::TRANSFORM_COMPONENT_BITMASK) {
			glm::mat4 tf = e->transform.matrix();
			//DP_TRACE("---------------------");
			//DP_TRACE("| {} | {} | {} | {} |", tf[0][0], tf[1][0], tf[2][0], tf[3][0]);
			//DP_TRACE("| {} | {} | {} | {} |", tf[0][1], tf[1][1], tf[2][1], tf[3][1]);
			//DP_TRACE("| {} | {} | {} | {} |", tf[0][2], tf[1][2], tf[2][2], tf[3][2]);
			//DP_TRACE("| {} | {} | {} | {} |", tf[0][3], tf[1][3], tf[2][3], tf[3][3]);
			//DP_TRACE("---------------------");
			//DP_TRACE("");
			Renderer::submit_draw(
			    e->mesh.mesh_shader,
			    e->mesh.mesh_va,
			    tf);
		}
	});

	Renderer::end_draw_scope();
}

void Scene::on_update_runtime(float delta_time)
{
	ASSERT(false, "Implement on_update_runtime");
}

void Scene::dump_data_to_disk() { }
void Scene::load_data_from_disk() { }

}
