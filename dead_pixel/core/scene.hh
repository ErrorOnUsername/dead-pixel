#pragma once

#include <core/memory.hh>
#include <core/scene_data.hh>
#include <gfx/camera.hh>

namespace DP {

struct Scene {
	char const* name;
	OwnPtr<SceneData> data;

	Scene(char const* name)
		: name(name)
		, data(make_own_ptr<SceneData>()) { }
	virtual ~Scene() = default;

	virtual void on_update_editor(float delta_time, RefPtr<Camera> camera) = 0;
	virtual void on_update_runtime(float delta_time) = 0;

	// TODO: Implement
	void dump_data_to_disk() { }

	// TODO: Implement
	void load_data_from_disk() { }
};

}
