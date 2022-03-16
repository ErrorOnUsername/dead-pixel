#pragma once

#include <core/events.hh>
#include <core/layer.hh>

struct ImGUILayer : DP::Layer {
	void on_update(float delta_time) override;
	void on_event(DP::Event&) override;
};
