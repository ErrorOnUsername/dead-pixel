#pragma once

#include <core/types.hh>

namespace DP {

struct WindowData {
	u32  width;
	u32  height;
	bool vsync_enabled;

	void (*event_callback)();
};

struct Window {
	void*      window_handle;
	WindowData data;

	Window(char const* title, u32 width, u32 height);
	~Window();

	void on_update();

	void set_title(char const* title);
	void set_dimensions(u32 width, u32 height);
	void enable_vsync(bool enabled);

	bool should_close();
};

}
