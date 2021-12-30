#pragma once

#include <core/core.hh>
#include <events/event.hh>

namespace DP {

class DP_API MouseMovedEvent : public Event {
public:
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	EVENT_CLASS_TYPE(MouseMoved)
	MouseMovedEvent(float x, float y)
		: m_mouse_x(x)
		, m_mouse_y(y)
	{ }

	inline float mouse_x() const { return m_mouse_x; }
	inline float mouse_y() const { return m_mouse_y; }

	virtual std::string to_string() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: x = " << m_mouse_x << " y = " << m_mouse_y;
		return ss.str();
	}
private:
	float m_mouse_x;
	float m_mouse_y;
};

class DP_API MouseScrolledEvent : public Event {
public:
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	EVENT_CLASS_TYPE(MouseScrolled)
	MouseScrolledEvent(float x_offset, float y_offset)
		: m_x_offset(x_offset)
		, m_y_offset(y_offset)
	{ }

	inline float x_offset() const { return m_x_offset; }
	inline float y_offset() const { return m_y_offset; }

	virtual std::string to_string() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: x_offset = " << m_x_offset << " y_offet = " << m_y_offset;
		return ss.str();
	}
private:
	float m_x_offset;
	float m_y_offset;
};

class MouseButtonEvent : public Event {
public:
	EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryMouse | EventCategoryInput)

	inline int button() const { return m_button; }
protected:
	MouseButtonEvent(int button)
		: m_button(button)
	{ }

	int m_button;
};

class DP_API MouseButtonPressedEvent : public MouseButtonEvent {
public:
	EVENT_CLASS_TYPE(MouseButtonPressed)

	MouseButtonPressedEvent(int button)
		: MouseButtonEvent(button)
	{ }

	virtual std::string to_string() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: button = " << m_button;
		return ss.str();
	}
};

class DP_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
	EVENT_CLASS_TYPE(MouseButtonReleased)

	MouseButtonReleasedEvent(int button)
		: MouseButtonEvent(button)
	{ }

	virtual std::string to_string() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: button = " << m_button;
		return ss.str();
	}
};

}
