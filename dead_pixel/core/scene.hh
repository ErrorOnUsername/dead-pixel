#pragma once

#include <core/scene_data.hh>
#include <gfx/camera.hh>

namespace DP {

struct Scene {
	char const* name;
	SceneData* data;

	Scene(char const* name)
		: name(name)
		, data(new SceneData()) { }
	~Scene() { delete data; }

	void on_update_editor(float delta_time, Camera* camera);
	void on_update_runtime(float delta_time);

	void dump_data_to_disk();
	void load_data_from_disk();
};

}
