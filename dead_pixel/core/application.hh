#pragma once

#include <core/layer.hh>
#include <core/types.hh>
#include <core/window.hh>

namespace DP::Application {

void init(u32 window_width, u32 window_height, char const* name = "Dead Pixel Application");

void run();

void push_layer(Layer*);
void pop_layer();

}
