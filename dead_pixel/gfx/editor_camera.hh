#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

	glm::vec2 initial_mouse_positon;

	EditorCamera();
	EditorCamera(float fov, float aspect_ratio, float near_clip_z, float far_clip_z);

	void on_update(float delta_time);

	inline void recalculate_projection_matrix() { projection_matrix = glm::perspective(fov, aspect_ratio, near_clip_z, far_clip_z); }

	inline void adjust_aspect_ratio(float ratio) { aspect_ratio = ratio; recalculate_projection_matrix(); }
};

};
