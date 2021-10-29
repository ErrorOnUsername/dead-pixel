#pragma once

#include <dppch.h>
#include <Core/Core.h>
#include <Events/Event.h>

namespace DP {

struct WindowProperties {
	WindowProperties(char const* window_title = "Dead Pixel",
	                 uint32_t window_width = 1280,
	                 uint32_t window_height = 720,
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
public:
	using EventCallback = std::function<void(Event&)>;

	static Window* create(WindowProperties const& window_properties = WindowProperties());
	virtual ~Window() { }

	virtual void on_update() = 0;

	virtual uint32_t width() const = 0;
	virtual uint32_t height() const = 0;
	virtual void set_is_vsync_enabled(bool enabled) = 0;
	virtual bool is_vsync_enabled() const = 0;

	virtual void set_event_callback(EventCallback const&) = 0;
};

}
