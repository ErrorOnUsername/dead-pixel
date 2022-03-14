#include "application.hh"

#include <core/memory.hh>
#include <core/window.hh>
#include <events/application_event.hh>
#include <events/event.hh>

namespace DP {

void* Application::current_window = nullptr;

Application::Application()
{
	window = make_own_ptr<Window>();
	window->set_event_callback(std::bind(&Application::on_event, this, std::placeholders::_1));
	current_window = window->window_handle;
}

Application::~Application() {}

void Application::on_event(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::on_window_close, this, std::placeholders::_1));

	for(auto it = layer_stack.end(); it != layer_stack.begin(); ) {
		if(e.handled())
			break;
		(*--it)->on_event(e);
	}
}

void Application::run()
{
	running = true;
	while(running) {

		float time       = (float)glfwGetTime();
		float delta_time = time - last_frame_time;
		last_frame_time  = time;

		for(auto* layer : layer_stack)
			layer->on_update(delta_time);

		window->on_update();
	}
}

bool Application::on_window_close(WindowCloseEvent& e)
{
	running = false;
	return true;
}

void Application::push_layer(Layer* layer)
{
	layer_stack.push_layer(layer);
}

void Application::push_overlay(Layer* overlay)
{
	layer_stack.push_overlay(overlay);
}

}
