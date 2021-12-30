#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <Core/Core.h>
#include <Events/Event.h>
#include <GFX/GraphicsContext.h>

namespace DP {

struct WindowProperties {
	WindowProperties(char const* window_title = "Dead Pixel",
	                 uint32_t window_width = 1280,
	                 uint32_t window_height = 1024,
	                 bool vsync_enabled = true)
		: title(window_title)
		, width(window_width)
		, height(window_height)
		, is_vsync_enabled(vsync_enabled)
	{ }

	char const* title;
	uint32_t width;
	uint32_t height;
	bool is_vsync_enabled;
};


class DP_API Window {
	using EventCallback = std::function<void(Event&)>;
	struct WindowData {
		const char* title;
		uint32_t width;
		uint32_t height;
		bool is_vsync_enabled;

		std::function<void(Event&)> event_callback;
	};

public:
	Window(WindowProperties const& window_properties = WindowProperties());
	~Window();

	void on_update();

	uint32_t width() const;
	uint32_t height() const;
	void set_is_vsync_enabled(bool enabled);
	bool is_vsync_enabled() const;

	void set_event_callback(EventCallback const& callback) { m_data.event_callback = callback; }
private:
	GLFWwindow* m_window;
	GraphicsContext* m_graphics_context;

	WindowData m_data;
};

}
