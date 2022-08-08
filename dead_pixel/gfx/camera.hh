#pragma once

#include <glm/glm.hpp>

namespace DP {

enum class ProjectionStyle {
	Orthographic,
	Perspective
};

struct Camera {
	ProjectionStyle projection_style;
	glm::mat4 projection_matrix;
	glm::mat4 pv_matrix;
	glm::vec3 position;
	// FIXME: This should probably be a quaternion...
	glm::vec3 rotation;
	float fov;
	float aspect_ratio;

	Camera(ProjectionStyle projection_style,
	       float aspect_ratio,
	       float fov    = 90.0f,
	       float left   = 0.0f,
	       float right  = 1.0f,
		   float bottom = 0.0f,
		   float top    = 1.0f);

	void set_projection_style(ProjectionStyle projection_style,
	                          float aspect_ratio,
	                          float fov    = 90.0f,
	                          float left   = 0.0f,
	                          float right  = 1.0f,
		                      float bottom = 0.0f,
		                      float top    = 1.0f);

	void set_aspect_ratio(float ratio);

	void set_fov(float fov);

	void set_ortho_bounds(float left, float right, float bottom, float top);
};

};
