#include "Buffer.h"

#include <Core/Pointer.h>
#include <Renderer/Renderer.h>
#include <Renderer/API/GraphicsAPI.h>
#include <Renderer/API/OpenGL/GLBuffer.h>

namespace DP {
shared_ptr<VertexBuffer> VertexBuffer::create(uint32_t size)
{
	switch(Renderer::api())
	{
		case GraphicsAPI::API::None: break;
		case GraphicsAPI::API::OpenGL: return create_shared_ptr<GLVertexBuffer>(size);
		case GraphicsAPI::API::Vulkan: break;
	}
	return nullptr;
}

shared_ptr<VertexBuffer> VertexBuffer::create(const void* data, uint32_t size)
{
	switch(Renderer::api())
	{
		case GraphicsAPI::API::None: break;
		case GraphicsAPI::API::OpenGL: return create_shared_ptr<GLVertexBuffer>((float*)data, size);
		case GraphicsAPI::API::Vulkan: break;
	}
	return nullptr;
}

shared_ptr<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t count)
{
	switch(Renderer::api())
	{
		case GraphicsAPI::API::None: break;
		case GraphicsAPI::API::OpenGL: return create_shared_ptr<GLIndexBuffer>(indices, count);
		case GraphicsAPI::API::Vulkan: break;
	}
	return nullptr;
}
}
