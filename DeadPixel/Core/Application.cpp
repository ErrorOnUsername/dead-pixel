#include "Application.h"

#include <dppch.h>
#include <Core/Window.h>
#include <Events/ApplicationEvent.h>
#include <Events/Event.h>

namespace DP {

Application::Application()
{
	m_window = std::unique_ptr<Window>(Window::create());
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
		(*--it)->on_event(e);
		if(e.handled())
			break;
	}
}

void Application::run()
{
	m_running = true;
	while(m_running) {
		for(auto* layer : m_layer_stack)
			layer->on_update();

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
