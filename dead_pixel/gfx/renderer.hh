#pragma once

#include <glm/glm.hpp>

#include <core/memory.hh>
#include <gfx/camera.hh>
#include <gfx/vertex_array.hh>
#include <gfx/shader.hh>
#include <gfx/vertex_array.hh>

namespace DP::Renderer {

void clear();
void set_clear_color(float r, float g, float b);

void begin_draw_scope(RefPtr<Camera> camera);
void end_draw_scope();

void submit_draw(RefPtr<Shader> shader, RefPtr<VertexArray> vertex_array, glm::mat4& transform);

}
