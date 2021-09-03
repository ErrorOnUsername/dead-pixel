#include "VertexArray.h"

#include <Core/Pointer.h>
#include <Renderer/Renderer.h>
#include <Renderer/API/OpenGL/GLVertexArray.h>

namespace DP {
shared_ptr<VertexArray> VertexArray::create()
{
	switch(Renderer::api())
	{
		case GraphicsAPI::API::None:
			break;
		case GraphicsAPI::API::OpenGL:
			return create_shared_ptr<GLVertexArray>();
		case GraphicsAPI::API::Vulkan:
			break;
	}
	return nullptr;
}
}