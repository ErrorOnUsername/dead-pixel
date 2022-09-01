#include "editor_camera.hh"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <core/events.hh>
#include <core/input.hh>
#include <core/input_codes.hh>
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
	, last_mouse_pos(0.0f)
{
	calculate_projection();
	calculate_view();
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
	, last_mouse_pos(0.0f)
{
	calculate_projection();
	calculate_view();
}

void EditorCamera::calculate_projection()
{
	projection_matrix = glm::perspective(fov, aspect_ratio, near_clip_z, far_clip_z);
}

void EditorCamera::calculate_view()
{
	position = calculate_position();

	glm::quat orientation = calculate_orientation();
	view_matrix = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(orientation);
	view_matrix = glm::inverse(view_matrix);
}

void EditorCamera::on_update(float delta_time)
{
	glm::vec2 mouse_pos = Input::mouse_position();
	glm::vec2 delta     = (mouse_pos - last_mouse_pos) * 0.008f;
	last_mouse_pos      = mouse_pos;
	if(Input::is_mouse_button_down(Input::Mouse::ButtonRight)) {
		float yaw_sign = up_direction().y < 0 ? -1.0f : 1.0f;
		yaw   += yaw_sign * delta.x;
		pitch += delta.y;
	}
	calculate_view();
}

bool on_mouse_scroll(EditorCamera&, MouseScrolledEvent&);

void EditorCamera::on_event(Event& e)
{
	EventDispacher dispacher(e);
	dispacher.dispatch<EditorCamera, MouseScrolledEvent>(*this, on_mouse_scroll);
}

bool on_mouse_scroll(EditorCamera& context, MouseScrolledEvent& e)
{
	context.distance -= e.y_offset;
	if(context.distance < 1.0f) context.distance = 1.0f;
	else if(context.distance > 20.0f) context.distance = 20.0f;
	return false;
}

glm::vec3 EditorCamera::calculate_position() const
{
	return focal_point - forward_direction() * distance;
}

glm::quat EditorCamera::calculate_orientation() const
{
	return glm::quat(glm::vec3(-pitch, -yaw, 0.0f));
}

glm::vec3 EditorCamera::up_direction() const
{
	return glm::rotate(calculate_orientation(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 EditorCamera::forward_direction() const
{
	return glm::rotate(calculate_orientation(), glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 EditorCamera::right_direction() const
{
	return glm::rotate(calculate_orientation(), glm::vec3(1.0f, 0.0f, 0.0f));
}

}
