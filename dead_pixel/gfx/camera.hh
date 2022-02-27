#pragma once

#include <glm/glm.hpp>

namespace DP {

struct PersectiveCamera {
	glm::vec3 position = {0.0f, 0.0f, 0.0f};
	glm::vec3 rotation = {0.0f, 0.0f, 0.0f};

	glm::mat4 projection_matrix;
	glm::mat4 view_matrix;
	glm::mat4 pv_matrix;

	PersectiveCamera(float aspect_ratio
	     , float near_plane = 0.01f
	     , float far_plane  = 1000.0f
	     , float fov        = 90.0f);

	void adjust_bounds(float aspect_ratio
	                 , float near_plane = 0.01f
	                 , float far_plane  = 1000.0f
	                 , float fov        = 90.0f);

	void set_position(float x, float y, float z);

private:
	void recalculate_view();
};

struct OrthographicCamera {
	glm::mat4 projection_matrix;
	glm::mat4 view_matrix;
	glm::mat4 pv_matrix;

	OrthographicCamera(float left , float right , float top , float bottom);

	void adjust_bounds(float left , float right , float top , float bottom);
};

}
