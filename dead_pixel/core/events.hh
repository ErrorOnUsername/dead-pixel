#pragma once

#include <core/types.hh>

namespace DP {

enum EventType : u8 {
	DP_EVENT_KEY_PRESSED = 0,
	DP_EVENT_KEY_RELEASED,

	DP_EVENT_MOUSE_BUTTON_PRESSED,
	DP_EVENT_MOUSE_BUTTON_RELEASED,
	DP_EVENT_MOUSE_MOVED,
	DP_EVENT_MOUSE_SCROLLED,

	DP_EVENT_WINDOW_CLOSED,
	DP_EVENT_WINDOW_RESIZED,
	DP_EVENT_WINDOW_MOVED,
	DP_EVENT_WINDOW_FOCUSED,
	DP_EVENT_WINDOW_LOST_FOCUS,
};

#define EVENT_TYPE(event_type) \
	static inline EventType static_type() { return EventType::event_type; } \
	EventType               type() const override { return static_type(); } \
	char const*             name() const override { return #event_type; }

struct Event {
	bool handled = false;

	virtual EventType   type() const = 0;
	virtual char const* name() const = 0;
};

struct EventDispacher {
	Event& event;

	EventDispacher(Event& e)
		: event(e)
	{ }

	template<typename ContextT, typename EventT>
	bool dispatch(ContextT& context, bool (*callback)(ContextT&, EventT&))
	{
		if(event.type() == EventT::static_type()) {
			event.handled = callback(context, *(EventT*)&event);
			return true;
		}

		return false;
	}
};

//////////////////////////////////////////////////
/////////////////   Key Events   /////////////////
//////////////////////////////////////////////////

struct KeyPressedEvent : Event {
	EVENT_TYPE(DP_EVENT_KEY_PRESSED);

	int  keycode;
	bool repeated;

	KeyPressedEvent(int keycode, bool repeated)
		: keycode(keycode)
		, repeated(repeated)
	{ }
};

struct KeyReleasedEvent : Event {
	EVENT_TYPE(DP_EVENT_KEY_RELEASED);

	int keycode;

	KeyReleasedEvent(int keycode)
		: keycode(keycode)
	{ }
};

//////////////////////////////////////////////////
//////////////   Mouse Events   //////////////////
//////////////////////////////////////////////////

struct MouseButtonPressedEvent : Event {
	EVENT_TYPE(DP_EVENT_MOUSE_BUTTON_PRESSED);

	int button;

	MouseButtonPressedEvent(int button)
		: button(button)
	{ }
};

struct MouseButtonReleasedEvent : Event {
	EVENT_TYPE(DP_EVENT_MOUSE_BUTTON_RELEASED);

	int button;

	MouseButtonReleasedEvent(int button)
		: button(button)
	{ }
};

struct MouseMovedEvent : Event {
	EVENT_TYPE(DP_EVENT_MOUSE_MOVED);

	float x_position;
	float y_position;

	MouseMovedEvent(float x_position, float y_position)
		: x_position(x_position)
		, y_position(y_position)
	{ }
};

struct MouseScrolledEvent : Event {
	EVENT_TYPE(DP_EVENT_MOUSE_SCROLLED);

	float x_offset;
	float y_offset;

	MouseScrolledEvent(float x_offset, float y_offset)
		: x_offset(x_offset)
		, y_offset(y_offset)
	{ }
};

//////////////////////////////////////////////////
///////////////  Window Events  //////////////////
//////////////////////////////////////////////////

struct WindowClosedEvent : Event {
	EVENT_TYPE(DP_EVENT_WINDOW_CLOSED);

	WindowClosedEvent() { }
};

struct WindowResizedEvent : Event {
	EVENT_TYPE(DP_EVENT_WINDOW_RESIZED);

	u32 width;
	u32 height;

	WindowResizedEvent(u32 width, u32 height)
		: width(width)
		, height(height)
	{ }
};

struct WindowFocusedEvent : Event {
	EVENT_TYPE(DP_EVENT_WINDOW_FOCUSED);

	WindowFocusedEvent() { }
};

struct WindowLostFocusEvent : Event {
	EVENT_TYPE(DP_EVENT_WINDOW_LOST_FOCUS);

	WindowLostFocusEvent() { }
};

}
