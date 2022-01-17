#pragma once

#include <core/core.hh>
#include <core/layer.hh>
#include <core/layer_stack.hh>
#include <core/memory.hh>
#include <core/window.hh>
#include <events/application_event.hh>

namespace DP {

class DP_API Application {
public:
	static void* current_window;

	Application();
	virtual ~Application();

	void run();
	void on_event(Event&);

	void push_layer(Layer*);
	void push_overlay(Layer*);

private:
	bool on_window_close(WindowCloseEvent&);

	OwnPtr<Window> m_window;

	bool m_running;
	float m_last_time;

	LayerStack m_layer_stack;
};

}
