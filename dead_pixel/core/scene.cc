#include "scene.hh"

#include <entity_system/components/bitmasks.hh>
#include <gfx/renderer.hh>

namespace DP {

void Scene::on_update_editor(float delta_time, EditorCamera *camera)
{
	Renderer::begin_draw_scope(camera);

	data->context.for_each([] (Entity* e) {
		if(e->component_bitfield & Component::MESH_COMPONENT_BITMASK &&
		   e->component_bitfield & Component::TRANSFORM_COMPONENT_BITMASK) {
			glm::mat4 tf = e->transform.matrix();
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
