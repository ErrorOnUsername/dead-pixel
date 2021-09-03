#include "GLGraphicsAPI.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <Core/Log.h>

namespace DP {
void gl_message_callback(unsigned source,
                         unsigned type,
                         unsigned id,
                         unsigned severity,
                         int length,
						 const char* message,
						 const void* userParam)
{
	switch(severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:
			DP_ENGINE_CRITICAL(message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			DP_ENGINE_ERROR(message);
			return;
		case GL_DEBUG_SEVERITY_LOW:
			DP_ENGINE_WARN(message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			DP_ENGINE_TRACE(message);
			break;
		default:
			break;
	}
}

void GLGraphicsAPI::init()
{
#ifdef DP_DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(gl_message_callback, nullptr);

	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
#endif
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
}

void GLGraphicsAPI::set_viewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
	glViewport(x, y, width, height);
}

void GLGraphicsAPI::set_clear_color(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void GLGraphicsAPI::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLGraphicsAPI::draw_indexed(const shared_ptr<VertexArray>& vertex_array, uint32_t vertex_count)
{
	uint32_t count = vertex_count ? vertex_count : vertex_array->index_buffer()->count();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}
}