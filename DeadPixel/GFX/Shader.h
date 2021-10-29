#pragma once

#include <glm/glm.hpp>

namespace DP {

struct Shader {
	uint32_t shader_id;

	Shader(char const* filepath);

	void bind();
	void unbind();

	void set_uniform_bool (char const* uniform_name, bool value);
	void set_uniform_int  (char const* uniform_name, int value);
	void set_uniform_float(char const* uniform_name, float value);
	void set_uniform_vec2 (char const* uniform_name, glm::vec2 value);
	void set_uniform_vec3 (char const* uniform_name, glm::vec3 value);
	void set_uniform_vec4 (char const* uniform_name, glm::vec4 value);
	void set_uniform_mat3 (char const* uniform_name, glm::mat3 value);
	void set_uniform_mat4 (char const* uniform_name, glm::mat4 value);
};

}
