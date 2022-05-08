#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace DP {

struct TransformComponent {
	glm::vec3 positon;
	glm::vec3 rotation;
	glm::vec3 scale;

	inline glm::mat4 matrix()
	{
		return glm::translate(glm::mat4(1.0), positon)
		     * glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f })
		     * glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f })
		     * glm::rotate(glm::mat4(1.0f), rotation.x, { 0.0f, 0.0f, 1.0f })
		     * glm::scale(glm::mat4(1.0f), scale);
	}
};

}
