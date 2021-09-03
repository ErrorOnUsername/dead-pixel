#pragma once
#include <string>
#include <ostream>

namespace DP {
enum class EventType {
	None = 0,
	WindowClose    , WindowFocus      , WindowLostFocus  , WindowResize      , WindowMove,
	KeyPress       , KeyRelease       ,
	MouseMove      , MouseScroll      , MouseButtonPress , MouseButtonRelease,
};

enum EventCategory {
	None        = 0b00000,
	Application = 0b00001,
	Input       = 0b00010,
	Keyboard    = 0b00100,
	Mouse       = 0b01000,
	MouseButton = 0b10000
};

#define EVENT_TYPE(event_type) static EventType static_type() { return EventType::event_type; }        \
                        virtual EventType type() const override { return static_type(); } \
                        virtual const char* name() const override { return #event_type; }

#define EVENT_CATEGORY(category) virtual int category_flags() const override { return category; }

class Event {
	friend class EventDispatcher;
public:
	virtual EventType type() const = 0;
	virtual int category_flags() const = 0;
	virtual const char* name() const = 0;
	virtual std::string to_str() const { return name(); }

	bool is_in_category(EventCategory category) {
		return category_flags() & category;
	}

protected:
	bool m_handled = false;
};

class EventDispatcher {
	template<typename T>
	using event_function = std::function<bool(T&)>;
public:
	EventDispatcher(Event& event)
		: m_event (event)
	{ }

	template<typename T>
	bool dispatch(event_function<T> function)
	{
		if(m_event.type() == T::static_type())
		{
			m_event.m_handled = function(*(T*)&m_event);
			return true;
		}
		return false;
	}

private:
	Event& m_event;
};

inline std::ostream& operator<<(std::ostream& os, Event& event)
{
	return os << event.to_str();
}
}