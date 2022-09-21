#include "core/file_utils.hh"
#include <cstring>
#include <stdio.h>
#include <unistd.h>

#include <glm/gtc/type_ptr.hpp>

#include <core/assert.hh>
#include <core/file_utils.hh>
#include <core/log.hh>
#include <gfx/shader.hh>

namespace DP {

static char const* find_shader_name_from_filepath(char const* filepath)
{
	usize filepath_length  = strlen(filepath);
	usize last_slash_index = 0;
	usize end_index        = 0;
	usize name_length      = 0;

	for(usize i = 0; i < filepath_length; i++) {
		if(filepath[i] == '/') {
			last_slash_index = i;
		} else if(filepath[i] == '.') {
			end_index = i;
		}
	}

	// name length is 4 ["file"]
	// we add one for null-terminator
	//
	// something/file.vert
	//          ^    ^
	//          9    14
	//
	//          14 - 9 = 5
	name_length = end_index - last_slash_index;
	char* name = (char*)malloc(name_length);
	strncpy(&name[0], &filepath[last_slash_index + 1], name_length - 1);
	name[name_length - 1] = 0;

	return (char const*)name;
}

Shader::Shader(char const* vert_filepath, char const* frag_filepath)
{
	// It doesn't really matter which one we pass to this. Well, that's not
	// entirely true, but for my purposes it doesn't matter, so I'm just gonna
	// use the fragment shader. Change it if the need arises.
	name = find_shader_name_from_filepath(frag_filepath);

	char const* vert_source = read_file(vert_filepath);
	char const* frag_source = read_file(frag_filepath);

	compile_code(vert_source, frag_source);

	delete vert_source;
	delete frag_source;
}

Shader::Shader(char const* shader_name
             , char const* vert_source
             , char const* frag_source)
{
	name = shader_name;

	compile_code(vert_source, frag_source);
}

Shader::~Shader()
{
	free((void*)name); // This would've been a leak :P
	glDeleteProgram(program_id);
}

void Shader::compile_code(char const* vert_source, char const* frag_source)
{
	u32 vertex_shader_id   = load_shader(GL_VERTEX_SHADER, vert_source);
	u32 fragment_shader_id = load_shader(GL_FRAGMENT_SHADER, frag_source);

	program_id = glCreateProgram();

	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);
	glValidateProgram(program_id);

	glDetachShader(program_id, vertex_shader_id);
	glDeleteShader(vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);
	glDeleteShader(fragment_shader_id);

	DP_ENGINE_TRACE("Shader [{0}:{1}] successfully compiled", name, program_id);
}

char const* Shader::read_file(char const* relative_filepath)
{
	return (char const*)FileUtils::read_file_from_relative_path(relative_filepath);
}

uint32_t Shader::load_shader(GLenum shader_type, char const* shader_source)
{
	u32 shader_id = glCreateShader(shader_type);

	glShaderSource(shader_id, 1, &shader_source, nullptr);
	glCompileShader(shader_id);

	i32 shader_compiled = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &shader_compiled);
	if(shader_compiled != GL_TRUE) {
		GLsizei log_size = 0;
		GLchar message[1024];
		glGetShaderInfoLog(shader_id, 1024, &log_size, message);

		DP_ENGINE_ERROR("{0}", (char const*)message);
	}

	return shader_id;
}

void Shader::bind()
{
	glUseProgram(program_id);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::set_uniform_int(char const* uniform_name, int value)
{
	GLint location = glGetUniformLocation(program_id, uniform_name);
	ASSERT_FMT(location != -1, "Could not find uniform: {0}", uniform_name);
	glUniform1i(location, value);
}

void Shader::set_uniform_float(char const* uniform_name, float value)
{
	GLint location = glGetUniformLocation(program_id, uniform_name);
	ASSERT_FMT(location != -1, "Could not find uniform: {0}", uniform_name);
	glUniform1f(location, value);
}

void Shader::set_uniform_vec2(char const* uniform_name, glm::vec2 value)
{
	GLint location = glGetUniformLocation(program_id, uniform_name);
	ASSERT_FMT(location != -1, "Could not find uniform: {0}", uniform_name);
	glUniform2f(location, value.x, value.y);
}

void Shader::set_uniform_vec3(char const* uniform_name, glm::vec3 value)
{
	GLint location = glGetUniformLocation(program_id, uniform_name);
	ASSERT_FMT(location != -1, "Could not find uniform: {0}", uniform_name);
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::set_uniform_vec4(char const* uniform_name, glm::vec4 value)
{
	GLint location = glGetUniformLocation(program_id, uniform_name);
	ASSERT_FMT(location != -1, "Could not find uniform: {0}", uniform_name);
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::set_uniform_mat3(char const* uniform_name, glm::mat3 value)
{
	GLint location = glGetUniformLocation(program_id, uniform_name);
	ASSERT_FMT(location != -1, "Could not find uniform: {0}", uniform_name);
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_uniform_mat4(char const* uniform_name, glm::mat4 value)
{
	GLint location = glGetUniformLocation(program_id, uniform_name);
	ASSERT_FMT(location != -1, "Could not find uniform: {0}", uniform_name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

}
