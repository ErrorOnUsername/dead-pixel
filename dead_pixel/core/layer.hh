#pragma once

#include <core/events.hh>

namespace DP {

struct Layer {
	virtual void on_attach() { }
	virtual void on_detach() { }

	virtual void on_update(float delta_time) = 0;
	virtual void on_event(Event& event) = 0;
	virtual void on_imgui_render() = 0;
};

}
