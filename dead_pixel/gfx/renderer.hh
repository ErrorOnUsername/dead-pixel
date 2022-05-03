#pragma once

#include <core/memory.hh>
#include <gfx/vertex_array.hh>

namespace DP::Renderer {

void clear();
void set_clear_color(float r, float g, float b);

void submit_draw(RefPtr<VertexArray> vertex_array);

}
