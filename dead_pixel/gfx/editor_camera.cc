#include "editor_camera.hh"

#include <core/log.hh>

namespace DP {

EditorCamera::EditorCamera()
	: fov(45.0f)
	, aspect_ratio(1.0f)
	, near_clip_z(0.1f)
	, far_clip_z(1000.0f)
	, projection_matrix(1.0f)
	, view_matrix(1.0f)
	, position(0.0f)
	, yaw(0.0f)
	, pitch(0.0f)
	, focal_point(0.0f)
	, distance(10.0f)
	, initial_mouse_positon(0.0f)
{
	projection_matrix = glm::perspective(fov, aspect_ratio, near_clip_z, far_clip_z);
}

EditorCamera::EditorCamera(float fov, float aspect_ratio, float near_clip_z, float far_clip_z)
	: fov(fov)
	, aspect_ratio(aspect_ratio)
	, near_clip_z(near_clip_z)
	, far_clip_z(far_clip_z)
	, projection_matrix(1.0f)
	, view_matrix(1.0f)
	, position(0.0f)
	, yaw(0.0f)
	, pitch(0.0f)
	, focal_point(0.0f)
	, distance(4.0f)
	, initial_mouse_positon(0.0f)
{
	projection_matrix = glm::perspective(fov, aspect_ratio, near_clip_z, far_clip_z);
}

void EditorCamera::on_update(float delta_time)
{ }

}
