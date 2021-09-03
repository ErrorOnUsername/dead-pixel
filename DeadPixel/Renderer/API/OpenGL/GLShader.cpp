#include "GLShader.h"

namespace DP {
GLShader::GLShader(std::string& filename)
{ }

GLShader::GLShader(std::string& name, std::string& vertex_source, std::string& fragment_source)
{ }

GLShader::~GLShader()
{ }

void GLShader::bind() const
{ }

void GLShader::unbind() const
{ }

void GLShader::set_int(const std::string& name, int32_t value)
{ }

void GLShader::set_int_array(const std::string& name, int32_t* values, uint32_t size)
{ }

void GLShader::set_float(const std::string& name, float value)
{ }

void GLShader::set_vec2(const std::string& name, const glm::vec2& vector)
{ }

void GLShader::set_vec3(const std::string& name, const glm::vec3& vector)
{ }

void GLShader::set_vec4(const std::string& name, const glm::vec4& vector)
{ }

void GLShader::set_mat4(const std::string& name, const glm::mat4& matrix)
{ }
}