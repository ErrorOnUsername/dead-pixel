#pragma once

#include <dppch.h>
#include <Core/Core.h>
#include <Core/Layer.h>

namespace DP {

class DP_API LayerStack {
public:
	LayerStack ();
	~LayerStack();

	void push_layer  (Layer*);
	void push_overlay(Layer*);
	void pop_layer   (Layer*);
	void pop_overlay (Layer*);

	std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
	std::vector<Layer*>::iterator end()   { return m_layers.end(); }
private:
	std::vector<Layer*> m_layers;
	std::vector<Layer*>::iterator m_layer_insert;
};

}
