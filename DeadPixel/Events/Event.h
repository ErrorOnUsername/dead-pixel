#pragma once

#include <dppch.h>
#include <Core/Core.h>

namespace DP {

enum class EventType {
	None = 0,
	WindowClose,        WindowResize,        WindowFocus, WindowLostFocus, WindowMoved,
	KeyPressed,         KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved,  MouseScrolled
};

enum EventCategory {
	None = 0,
	EventCategoryApplication = 0b00000,
	EventCategoryInput       = 0b00010,
	EventCategoryKeyboard    = 0b00100,
	EventCategoryMouse       = 0b01000,
	EventCategoryMouseButton = 0b10000,
};

#define EVENT_CLASS_TYPE(event_type) static EventType static_type() { return EventType::event_type; }  \
                                     virtual EventType type() const override { return static_type(); } \
                                     virtual const char* name() const override { return #event_type; }

#define EVENT_CLASS_CATEGORY(category) virtual int category_flags() const override { return category; }

class DP_API Event {
	friend class EventDispatcher;
public:
	virtual EventType type()        const = 0;
	virtual int category_flags()    const = 0;
	virtual const char* name()      const = 0;
	virtual std::string to_string() const { return name(); }

	inline bool is_in_category(EventCategory category) { return category_flags() & category; }

	inline bool handled() const { return m_handled; }
protected:
	bool m_handled = false;
};

class EventDispatcher {
	template<typename T>
	using EventCallback = std::function<bool(T&)>;
public:
	EventDispatcher(Event& event)
		: m_event(event)
	{ }

	template<typename T>
	bool dispatch(EventCallback<T> fn)
	{
		if(m_event.type() == T::static_type()) {
			m_event.m_handled = fn(*(T*)&m_event);
			return true;
		}

		return false;
	}

private:
	Event& m_event;
};

}
