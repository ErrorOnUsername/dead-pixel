#include "camera.hh"

#include <glm/gtc/matrix_transform.hpp>

namespace DP {

PersectiveCamera::PersectiveCamera(float aspect_ratio
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

void PersectiveCamera::adjust_bounds(float aspect_ratio
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

void PersectiveCamera::set_position(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	recalculate_view();
}

void PersectiveCamera::recalculate_view()
{
	view_matrix = glm::translate(glm::mat4(1.0f), position);
	glm::rotate(view_matrix, rotation.x, {1.0f, 0.0f, 0.0f});
	glm::rotate(view_matrix, rotation.y, {0.0f, 1.0f, 0.0f});
	glm::rotate(view_matrix, rotation.z, {0.0f, 0.0f, 1.0f});

	pv_matrix = projection_matrix * view_matrix;
}

OrthographicCamera::OrthographicCamera(float left
                                     , float right
                                     , float top
                                     , float bottom)
	: projection_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
	, view_matrix(1.0f)
{
	pv_matrix = projection_matrix * view_matrix;
}

void OrthographicCamera::adjust_bounds(float left
                                     , float right
                                     , float top
                                     , float bottom)
{
	projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	pv_matrix = projection_matrix * view_matrix;
}

}
