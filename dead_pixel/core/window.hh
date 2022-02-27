#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <core/core.hh>
#include <events/event.hh>
#include <gfx/graphics_context.hh>

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


struct Window {
	using EventCallback = std::function<void(Event&)>;

	struct WindowData {
		const char* title;
		uint32_t width;
		uint32_t height;
		bool is_vsync_enabled;

		EventCallback event_callback;
	};

	GLFWwindow*      window_handle;
	GraphicsContext* graphics_context;
	WindowData       data;

	Window(WindowProperties const& window_properties = WindowProperties());
	~Window();

	void on_update();

	uint32_t width() const;
	uint32_t height() const;
	void set_is_vsync_enabled(bool enabled);
	bool is_vsync_enabled() const;

	void set_event_callback(EventCallback callback) { data.event_callback = callback; }
};

}
