#include <core/scene.hh>
#include <core/memory.hh>
#include <gfx/camera.hh>
#include <gfx/vertex_array.hh>
#include <gfx/shader.hh>

struct TestScene : public DP::Scene {
	DP::RefPtr<DP::VertexArray> cube_va;
	DP::RefPtr<DP::Shader>      cube_shader;

	static DP::RefPtr<TestScene> create() { return DP::make_ref_ptr<TestScene>(); }

	TestScene();

	virtual void on_update_editor(float delta_time, DP::RefPtr<DP::Camera> editor_camera) override;
	virtual void on_update_runtime(float delta_time) override;
};
