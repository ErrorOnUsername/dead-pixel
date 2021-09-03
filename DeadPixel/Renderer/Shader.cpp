#include "Shader.h"

#include <Core/Pointer.h>
#include <Renderer/API/OpenGL/GLShader.h>
#include <Renderer/Renderer.h>

namespace DP {
shared_ptr<Shader> Shader::create(std::string& filepath)
{
	switch(Renderer::api())
	{
		case GraphicsAPI::API::None: break;
		case GraphicsAPI::API::OpenGL: return create_shared_ptr<GLShader>(filepath);
		case GraphicsAPI::API::Vulkan: break;
	}
	return nullptr;
}

shared_ptr<Shader> Shader::create(std::string& name, std::string& vertex_source, std::string& fragment_source)
{
	switch(Renderer::api())
	{
		case GraphicsAPI::API::None: break;
		case GraphicsAPI::API::OpenGL: return create_shared_ptr<GLShader>(name, vertex_source, fragment_source);
		case GraphicsAPI::API::Vulkan: break;
	}
	return nullptr;
}
}
