#pragma once

#include <core/core.hh>
#include <events/event.hh>

namespace DP {

class DP_API Layer {
public:
	Layer(char const* name = "Layer");
	virtual ~Layer();

	virtual void on_attach() { }
	virtual void on_detach() { }
	virtual void on_update(float delta_time) { }
	virtual void on_event (Event&) { }

	inline char const* name() const { return m_name; }
private:
	char const* m_name;
};

}
