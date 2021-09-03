#include "GraphicsAPI.h"

#include <Core/Pointer.h>
#include <Renderer/API/OpenGL/GLGraphicsAPI.h>

namespace DP {
GraphicsAPI::API GraphicsAPI::s_api;
unique_ptr<GraphicsAPI> GraphicsAPI::create()
{
	switch(s_api)
	{
		case API::None: break;
		case API::OpenGL: return create_unique_ptr<GLGraphicsAPI>();
		case API::Vulkan: break;
	}
	return nullptr;
}
}
