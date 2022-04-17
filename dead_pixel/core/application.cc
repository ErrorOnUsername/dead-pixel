#include "application.hh"

#include <core/events.hh>
#include <core/imgui_layer.hh>
#include <core/layer.hh>
#include <core/time.hh>
#include <core/types.hh>

namespace DP::Application {

#define MAX_LAYER_COUNT 8
static i16    last_index = -1;
static Layer* layers[MAX_LAYER_COUNT];

static ImGuiLayer* main_imgui_layer;

static Window* window;

static float last_frame_time;

static void on_event(Event& e);

void init(u32 window_width, u32 window_height, char const* name)
{
	window = new Window(name, window_width, window_height);
	window->data.event_callback = &on_event;

	main_imgui_layer = new ImGuiLayer();

	push_layer(main_imgui_layer);
}

static void cleanup()
{
	delete window;
	delete main_imgui_layer;
}

static void on_event(Event& e)
{
	for(i16 i = 0; i < MAX_LAYER_COUNT; i++) {
		if(e.handled) break;
		if(layers[i]) layers[i]->on_event(e);
	}
}

void run()
{
	while(!window->should_close()) {
		float current_time = Time::seconds_since_start();
		float delta_time = current_time - last_frame_time;
		last_frame_time = current_time;

		for(i16 i = 0; i < MAX_LAYER_COUNT; i++) {
			if(layers[i])
				layers[i]->on_update(delta_time);
		}

		main_imgui_layer->begin();
		for(i16 i = 0; i < MAX_LAYER_COUNT; i++) {
			if(layers[i])
				layers[i]->on_imgui_render();
		}
		main_imgui_layer->end();

		window->on_update();
	}

	cleanup();
}

Window* current_window()
{
	return window;
}

void push_layer(Layer* layer)
{
	layers[++last_index] = layer;
	layer->on_attach();
}

void pop_layer()
{
	layers[last_index]->on_detach();
	layers[last_index--] = nullptr;
}

}
