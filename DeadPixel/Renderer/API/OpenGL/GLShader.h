#pragma once
#include <cstdint>
#include <string>

#include <glm/glm.hpp>

#include <Renderer/Shader.h>

namespace DP {
class GLShader : public Shader {
public:
	GLShader(std::string& filename);
	GLShader(std::string& name, std::string& vertex_source, std::string& fragment_source);
	~GLShader();

	void bind() const override;
	void unbind() const override;

	void set_int(const std::string& name, int32_t value) override;
	void set_int_array(const std::string& name, int32_t* values, uint32_t size) override;

	void set_float(const std::string& name, float value) override;
	void set_vec2(const std::string& name, const glm::vec2& vector) override;
	void set_vec3(const std::string& name, const glm::vec3& vector) override;
	void set_vec4(const std::string& name, const glm::vec4& vector) override;
	void set_mat4(const std::string& name, const glm::mat4& matrix) override;
};
}