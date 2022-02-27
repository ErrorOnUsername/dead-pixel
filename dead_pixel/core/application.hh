#pragma once

#include <core/core.hh>
#include <core/layer.hh>
#include <core/layer_stack.hh>
#include <core/memory.hh>
#include <core/window.hh>
#include <events/application_event.hh>

namespace DP {

struct Application {
	using EventCallback = std::function<void(Event&)>;

	static void* current_window;

	OwnPtr<Window> window;
	LayerStack     layer_stack;
	bool           running;
	float          last_frame_time;

	Application();
	virtual ~Application();

	void run();
	void on_event(Event&);

	void push_layer(Layer*);
	void push_overlay(Layer*);

	bool on_window_close(WindowCloseEvent&);
};

}
