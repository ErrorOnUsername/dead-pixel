#pragma once
#include <cstdint>
#include <sstream>

#include <Events/Event.h>

namespace DP {
class WindowCloseEvent : public Event {
public:
	WindowCloseEvent()
	{ }

	EVENT_TYPE(WindowClose)
	EVENT_CATEGORY(Application)
};

class WindowFocusEvent : public Event {
public:
	WindowFocusEvent()
	{ }

	EVENT_TYPE(WindowFocus)
	EVENT_CATEGORY(Application)
};

class WindowLostFocusEvent : public Event {
public:
	WindowLostFocusEvent()
	{ }

	EVENT_TYPE(WindowLostFocus)
	EVENT_CATEGORY(Application)
};

class WindowResizeEvent : public Event {
public:
	WindowResizeEvent(uint32_t width, uint32_t height)
		: m_width  (width)
		, m_height (height)
	{ }

	inline uint32_t width() const { return m_width; }
	inline uint32_t height() const { return m_height; }

	std::string to_str() const override
	{
		std::stringstream ss;
		ss << "[WindowResizeEvent] width: " << m_width << " height: " << m_height;
		return ss.str();
	}

	EVENT_TYPE(WindowResize)
	EVENT_CATEGORY(Application)

private:
	uint32_t m_width;
	uint32_t m_height;
};
}