#include "application.hh"

#include <core/layer.hh>
#include <core/time.hh>
#include <core/types.hh>

namespace DP::Application {

#define MAX_LAYER_COUNT 8
static i16    last_index = -1;
static Layer* layers[MAX_LAYER_COUNT];

static Window* window;

static float last_frame_time;

void init(u32 window_width, u32 window_height, char const* name)
{
	window = new Window(name, window_width, window_height);
}

static void cleanup()
{
	delete window;
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

		window->on_update();
	}

	cleanup();
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
