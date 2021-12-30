#include <stdio.h>

#include <glm/gtc/type_ptr.hpp>

#include <core/assert.hh>
#include <core/log.hh>
#include <gfx/shader.hh>

namespace DP {

Shader::Shader(char const* vert_filepath, char const* frag_filepath)
{
	// TODO: Extract the shader name from the filepath
	name = "FIND THE NAME";

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
	glDeleteProgram(program_id);
}

void Shader::compile_code(char const* vert_source, char const* frag_source)
{
	uint32_t vertex_shader_id   = load_shader(GL_VERTEX_SHADER, vert_source);
	uint32_t fragment_shader_id = load_shader(GL_FRAGMENT_SHADER, frag_source);

	program_id = glCreateProgram();

	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);
	glValidateProgram(program_id);

	glDetachShader(program_id, vertex_shader_id);
	glDeleteShader(vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);
	glDeleteShader(fragment_shader_id);
}

char const* Shader::read_file(char const* filepath)
{
	FILE* file = fopen(filepath, "r");
	ASSERT_FMT(file, "Could not find file at path: {0}!!!", filepath);

	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);

	void* data = malloc(size + 1);
	fread(data, 1, size, file);
	fclose(file);

	((uint8_t*)data)[size] = 0;
	return (char const*)data;
}

uint32_t Shader::load_shader(GLenum shader_type, char const* shader_source)
{
	uint32_t shader_id = glCreateShader(shader_type);

	glShaderSource(shader_id, 1, &shader_source, nullptr);
	glCompileShader(shader_id);

	int32_t shader_compiled = 0;
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
	glUniform1i(location, value);
}

void Shader::set_uniform_float(char const* uniform_name, float value)
{
	GLint location = glGetUniformLocation(program_id, uniform_name);
	glUniform1f(location, value);
}

void Shader::set_uniform_vec2(char const* uniform_name, glm::vec2 value)
{
	GLint location = glGetUniformLocation(program_id, uniform_name);
	glUniform2f(location, value.x, value.y);
}

void Shader::set_uniform_vec3(char const* uniform_name, glm::vec3 value)
{
	GLint location = glGetUniformLocation(program_id, uniform_name);
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::set_uniform_vec4(char const* uniform_name, glm::vec4 value)
{
	GLint location = glGetUniformLocation(program_id, uniform_name);
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::set_uniform_mat3(char const* uniform_name, glm::mat3 value)
{
	GLint location = glGetUniformLocation(program_id, uniform_name);
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_uniform_mat4(char const* uniform_name, glm::mat4 value)
{
	GLint location = glGetUniformLocation(program_id, uniform_name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}


}
