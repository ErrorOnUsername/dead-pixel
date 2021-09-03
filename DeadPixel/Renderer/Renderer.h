#pragma once

#include <glad/glad.h>

#include <Renderer/API/GraphicsAPI.h>

namespace DP {
class Renderer {
public:
	static GraphicsAPI::API api() { return GraphicsAPI::api(); }

	static void clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
	static void set_clear_color(float red, float green, float blue) { glClearColor(red, green, blue, 1.0f); }
};
}
