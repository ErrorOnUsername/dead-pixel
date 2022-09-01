#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <core/events.hh>

namespace DP {

struct EditorCamera {
	float fov;
	float aspect_ratio;
	float near_clip_z;
	float far_clip_z;

	glm::mat4 projection_matrix;
	glm::mat4 view_matrix;
	glm::vec3 position;
	float yaw;
	float pitch;

	glm::vec3 focal_point;
	float distance;

	glm::vec2 last_mouse_pos;

	EditorCamera();
	EditorCamera(float fov, float aspect_ratio, float near_clip_z, float far_clip_z);

	void calculate_view();
	void calculate_projection();

	void on_update(float delta_time);
	void on_event(Event&);

	inline void recalculate_projection_matrix() { projection_matrix = glm::perspective(fov, aspect_ratio, near_clip_z, far_clip_z); }

	inline void adjust_aspect_ratio(float ratio) { aspect_ratio = ratio; recalculate_projection_matrix(); }

	glm::vec3 calculate_position() const;
	glm::quat calculate_orientation() const;

	glm::vec3 up_direction() const;
	glm::vec3 forward_direction() const;
	glm::vec3 right_direction() const;
};

};
