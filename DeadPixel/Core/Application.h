#pragma once

#include <Core/Core.h>
#include <Core/Layer.h>
#include <Core/LayerStack.h>
#include <Core/Memory.h>
#include <Core/Window.h>
#include <Events/ApplicationEvent.h>

namespace DP {

class DP_API Application {
public:
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
