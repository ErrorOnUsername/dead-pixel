#include "camera.hh"

#include <glm/gtc/matrix_transform.hpp>

#include <core/log.hh>

namespace DP {

Camera::Camera(ProjectionStyle projection_style,
               float aspect_ratio, float fov,
               float left,         float right,
               float bottom,       float top)
	: projection_style(projection_style)
	, pv_matrix(0.0f)
	, position(0.0f)
	, rotation(0.0f)
	, fov(fov)
	, aspect_ratio(aspect_ratio)
{
	switch(projection_style) {
		case ProjectionStyle::Orthographic : {
			projection_matrix = glm::ortho(left, right, bottom, top);

			glm::mat4 view_mat = glm::translate(glm::mat4(1.0f), position)
							   * glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f })
							   * glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f })
							   * glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f, 0.0f, 1.0f });

			pv_matrix = projection_matrix * view_mat;
			break;
		}
		case ProjectionStyle::Perspective : {
			projection_matrix = glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f);

			glm::mat4 view_mat = glm::translate(glm::mat4(1.0f), position)
							   * glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f })
							   * glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f })
							   * glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f, 0.0f, 1.0f });

			pv_matrix = projection_matrix * view_mat;
			break;
		}
	}
}

void Camera::set_projection_style(ProjectionStyle projection_style,
                                  float aspect_ratio, float fov,
                                  float left,         float right,
                                  float bottom,       float top)
{
	if(this->projection_style == projection_style) return;

	switch(projection_style) {
		case ProjectionStyle::Orthographic : {
			projection_matrix = glm::ortho(left, right, bottom, top);

			glm::mat4 view_mat = glm::translate(glm::mat4(1.0f), position)
							   * glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f })
							   * glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f })
							   * glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f, 0.0f, 1.0f });

			pv_matrix = projection_matrix * view_mat;
			break;
		}
		case ProjectionStyle::Perspective : {
			this->fov          = fov;
			this->aspect_ratio = aspect_ratio;
			projection_matrix  = glm::perspective(glm::radians(fov), aspect_ratio, 0.01f, 100.0f);

			glm::mat4 view_mat = glm::translate(glm::mat4(1.0f), position)
							   * glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f })
							   * glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f })
							   * glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f, 0.0f, 1.0f });

			pv_matrix = projection_matrix * view_mat;
			break;
		}
	}
}

void Camera::set_aspect_ratio(float ratio)
{
	aspect_ratio = ratio;
	projection_matrix = glm::perspective(glm::radians(fov), ratio, 0.01f, 100.0f);

	glm::mat4 view_mat = glm::translate(glm::mat4(1.0f), position)
	                   * glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f })
	                   * glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f })
	                   * glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f, 0.0f, 1.0f });

	pv_matrix = projection_matrix * view_mat;
}

void Camera::set_fov(float fov)
{
	this->fov = fov;
	projection_matrix = glm::perspective(glm::radians(fov), aspect_ratio, 0.01f, 100.0f);

	glm::mat4 view_mat = glm::translate(glm::mat4(1.0f), position)
	                   * glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f })
	                   * glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f })
	                   * glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f, 0.0f, 1.0f });

	pv_matrix = projection_matrix * view_mat;
}

void Camera::set_ortho_bounds(float left, float right, float bottom, float top)
{
	projection_matrix = glm::ortho(left, right, bottom, top);

	glm::mat4 view_mat = glm::translate(glm::mat4(1.0f), position)
	                   * glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f })
	                   * glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f })
	                   * glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f, 0.0f, 1.0f });

	pv_matrix = projection_matrix * view_mat;
}

}
