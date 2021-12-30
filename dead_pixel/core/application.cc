#include "application.hh"

#include <core/memory.hh>
#include <core/window.hh>
#include <events/application_event.hh>
#include <events/event.hh>

namespace DP {

Application::Application()
{
	m_window = make_own_ptr<Window>();
	m_window->set_event_callback(std::bind(&Application::on_event,
	                                       this,
	                                       std::placeholders::_1));
}

Application::~Application() {}

void Application::on_event(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::on_window_close,
	                                                this,
	                                                std::placeholders::_1));

	for(auto it = m_layer_stack.end(); it != m_layer_stack.begin(); ) {
		if(e.handled())
			break;
		(*--it)->on_event(e);
	}
}

void Application::run()
{
	m_running = true;
	while(m_running) {

		float time = (float)glfwGetTime();
		float delta_time = time - m_last_time;
		m_last_time = time;

		for(auto* layer : m_layer_stack)
			layer->on_update(delta_time);

		m_window->on_update();
	}
}

bool Application::on_window_close(WindowCloseEvent& e)
{
	m_running = false;
	return true;
}

void Application::push_layer(Layer* layer)
{
	m_layer_stack.push_layer(layer);
}

void Application::push_overlay(Layer* overlay)
{
	m_layer_stack.push_overlay(overlay);
}

}
