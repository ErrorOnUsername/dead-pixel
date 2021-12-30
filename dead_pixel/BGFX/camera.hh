#pragma once

#include <glm/glm.hpp>

namespace DP {

struct Camera {
	glm::vec3 position = {0.0f, 0.0f, 0.0f};
	glm::vec3 rotation = {0.0f, 0.0f, 0.0f};

	glm::mat4 projection_matrix;
	glm::mat4 view_matrix;
	glm::mat4 pv_matrix;

	Camera(float aspect_ratio
	     , float near_plane = 0.01f
	     , float far_plane  = 1000.0f
	     , float fov        = 90.0f);

	void adjust_bounds(float aspect_ratio
	                 , float near_plane = 0.01f
	                 , float far_plane  = 1000.0f
	                 , float fov        = 90.0f);

private:
	void recalculate_view();
};

}
