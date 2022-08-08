#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <core/types.hh>

namespace DP {

struct Shader {
	char const* name;
	u32    program_id;

	Shader(char const* shader_name
	     , char const* vert_source
	     , char const* frag_source);
	Shader(char const* vert_filepath, char const* frag_filepath);

	~Shader();

	void        compile_code(char const* vert_source, char const* frag_source);
	char const* read_file   (char const* filepath);
	u32         load_shader (GLenum shader_type, char const* shader_source);

	void bind  ();
	void unbind();

	void set_uniform_int  (char const* uniform_name, int value);
	void set_uniform_float(char const* uniform_name, float value);
	void set_uniform_vec2 (char const* uniform_name, glm::vec2 value);
	void set_uniform_vec3 (char const* uniform_name, glm::vec3 value);
	void set_uniform_vec4 (char const* uniform_name, glm::vec4 value);
	void set_uniform_mat3 (char const* uniform_name, glm::mat3 value);
	void set_uniform_mat4 (char const* uniform_name, glm::mat4 value);
};

}
