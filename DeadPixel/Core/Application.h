#pragma once
#include <string>

#include <Core/Layer.h>
#include <Core/Window.h>
#include <Events/Event.h>
#include <Events/ApplicationEvent.h>

namespace DP {

class Application {
public:
	static Application& the() { return *s_instance; }

	Application(std::string const& app_name = "Dead Pixel App");
	~Application();

	void on_event(Event& e);

	void push_layer(Layer* layer);
	void push_overlay(Layer* layer);

	void close();

	Window& window();

private:
	void run();
	void on_window_close(WindowCloseEvent& e);
	void on_window_resize(WindowResizeEvent& e);

	static Application* s_instance;
};

}
