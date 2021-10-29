#pragma once

#include <Core/Layer.h>
#include <Events/Event.h>

class GameLayer : public DP::Layer {
public:
	GameLayer();

	virtual void on_update() override;
	virtual void on_event(DP::Event&) override;
};
