#pragma once
#include <cstdint>
#include <string>

#include <glm/glm.hpp>

#include <Core/Pointer.h>

namespace DP {
class Shader {
public:
	virtual ~Shader() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual void set_int(const std::string& name, int32_t value) = 0;
	virtual void set_int_array(const std::string& name, int32_t* values, uint32_t size) = 0;

	virtual void set_float(const std::string& name, float value) = 0;
	virtual void set_vec2(const std::string& name, const glm::vec2& vector) = 0;
	virtual void set_vec3(const std::string& name, const glm::vec3& vector) = 0;
	virtual void set_vec4(const std::string& name, const glm::vec4& vector) = 0;
	virtual void set_mat4(const std::string& name, const glm::mat4& matrix) = 0;

	static shared_ptr<Shader> create(std::string& filepath);
	static shared_ptr<Shader> create(std::string& name, std::string& vertex_source, std::string& fragment_source);
};
}