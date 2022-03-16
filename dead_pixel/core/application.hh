#pragma once

#include <core/layer.hh>
#include <core/types.hh>
#include <core/window.hh>

namespace DP {

struct Application {
	Window window;

	float last_frame_time = 0.0f;
	float delta_time      = 0.0f;

	Application(u32 window_width, u32 window_height, char const* name = "Dead Pixel Application");
	~Application();

	void run();

	void push_layer(Layer*);
	void pop_layer();
};

}
