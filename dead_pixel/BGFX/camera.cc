#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace DP {

Camera::Camera(float aspect_ratio
             , float near_plane
             , float far_plane
             , float fov)
	: projection_matrix(glm::perspective(glm::radians(fov)
	                                   , aspect_ratio
	                                   , near_plane
	                                   , far_plane))
{
	recalculate_view();
}

void Camera::adjust_bounds(float aspect_ratio
                         , float near_plane
                         , float far_plane
                         , float fov)
{
	projection_matrix = glm::perspective(glm::radians(fov)
	                                   , aspect_ratio
	                                   , near_plane
	                                   , far_plane);

	recalculate_view();
}

void Camera::recalculate_view()
{
	view_matrix = glm::translate(glm::mat4(1.0f), position);
	glm::rotate(view_matrix, rotation.x, {1.0f, 0.0f, 0.0f});
	glm::rotate(view_matrix, rotation.y, {0.0f, 1.0f, 0.0f});
	glm::rotate(view_matrix, rotation.z, {0.0f, 0.0f, 1.0f});

	pv_matrix = projection_matrix * view_matrix;
}

}
