#pragma once
#include <sstream>

#include <Core/Core.h>
#include <Events/Event.h>

namespace DP {

class DP_API WindowResizeEvent : public Event {
public:
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
	EVENT_CLASS_TYPE(WindowResize)

	WindowResizeEvent(unsigned int width, unsigned int height)
		: m_width(width)
		, m_height(height)
	{ }

	inline unsigned int width() const { return m_width; }
	inline unsigned int height() const { return m_height; }

	virtual std::string to_string() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_width << "X" << m_height;
		return ss.str();
	}
private:
	unsigned int m_width;
	unsigned int m_height;
};

class DP_API WindowCloseEvent : public Event {
public:
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
	EVENT_CLASS_TYPE(WindowClose)

	WindowCloseEvent() {}
};

}
