#pragma once

#include <core/events.hh>
#include <core/layer.hh>

namespace DP {

struct ImGuiLayer : Layer {
	ImGuiLayer() = default;
	~ImGuiLayer() = default;

	void on_attach();
	void on_detach();

	void on_update(float) { }
	void on_event(Event&) { }

	void on_imgui_render() { }

	void begin();
	void end();
};

}
