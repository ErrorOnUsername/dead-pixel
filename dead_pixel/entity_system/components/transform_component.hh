#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace DP {

struct TransformComponent {
	glm::vec3 positon;
	glm::vec3 rotation;
	glm::vec3 scale;

	TransformComponent()
		: positon(0.0f)
		, rotation(0.0f)
		, scale(1.0f)
	{ }

	inline glm::mat4 matrix()
	{
		glm::mat4 ret = glm::translate(glm::mat4(1.0f), positon)
		              * glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f })
		              * glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f })
		              * glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f, 0.0f, 1.0f })
		              * glm::scale(glm::mat4(1.0f), scale);

		return ret;
	}
};

}
