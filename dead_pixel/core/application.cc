#include "application.hh"
#include <vector>
#include <cstdio>

#include <core/layer.hh>
#include <core/time.hh>
#include <core/types.hh>

namespace DP {

#define MAX_LAYER_COUNT 8
static i16    last_index = -1;
static Layer* layers[MAX_LAYER_COUNT];

Application::Application(u32 window_width, u32 window_height, char const* name)
	: window(name, window_width, window_height)
{ }

Application::~Application() { }

void Application::run()
{
	while(!window.should_close()) {
		// FIXME: Do this platform agnostically
		float current_time = Time::seconds_since_start();
		float delta_time = current_time - last_frame_time;
		last_frame_time = current_time;

		for(i16 i = MAX_LAYER_COUNT - 1; i >= 0; i--) {
			if(layers[i]) {
				layers[i]->on_update(delta_time);
			}
		}

		window.on_update();
	}
}

void Application::push_layer(Layer* layer)
{
	layers[++last_index] = layer;
	layer->on_attach();
}

void Application::pop_layer()
{
	layers[last_index]->on_detach();
	layers[last_index--] = nullptr;
}

}
