#pragma once
#include "Event.h"

#include <cstdint>
#include <sstream>

namespace DP {
class MouseMoveEvent : public Event {
public:
	MouseMoveEvent(float x, float y)
		: m_mouse_x(x)
		, m_mouse_y(y)
	{ }

	inline float x() const { return m_mouse_x; }
	inline float y() const { return m_mouse_y; }

	std::string to_str() const override
	{
		std::stringstream ss;
		ss << "[MouseMoveEvent] x: " << m_mouse_x << " y: " << m_mouse_y;
		ss.str();
	}

	EVENT_TYPE(MouseMove)
	EVENT_CATEGORY(Mouse | Input)

private:
	float m_mouse_x;
	float m_mouse_y;
};

class MouseScrollEvent : public Event {
public:
	MouseScrollEvent(int32_t x_offset, int32_t y_offset)
		: m_x_offset(x_offset)
		, m_y_offset(y_offset)
	{ }

	inline int32_t x_offset() const { return m_x_offset; }
	inline int32_t y_offset() const { return m_y_offset; }

	std::string to_str() const override
	{
		std::stringstream ss;
		ss << "[MouseScrollEvent] x_offset: " << m_x_offset << " y_offset: " << m_y_offset;
		return ss.str();
	}

	EVENT_TYPE(MouseScroll)
	EVENT_CATEGORY(Mouse | Input)

private:
	int32_t m_x_offset;
	int32_t m_y_offset;
};

class MouseButtonEvent : public Event {
public:
	int32_t mouse_button() { return m_button; }

	EVENT_CATEGORY(Mouse | MouseButton | Input)

protected:
	MouseButtonEvent(int32_t button)
		: m_button(button)
	{ }

	int32_t m_button;
};

class MouseButtonPressEvent : public MouseButtonEvent {
public:
	MouseButtonPressEvent(int32_t button)
		: MouseButtonEvent(button)
	{ }

	std::string to_str() const override
	{
		std::stringstream ss;
		ss << "[MouseButtonPressEvent] button: " << m_button;
		ss.str();
	}

	EVENT_TYPE(MouseButtonPress)
};

class MouseButtonReleaseEvent : public MouseButtonEvent {
public:
	MouseButtonReleaseEvent(int32_t button)
			: MouseButtonEvent(button)
	{ }

	std::string to_str() const override
	{
		std::stringstream ss;
		ss << "[MouseButtonReleaseEvent] button: " << m_button;
		ss.str();
	}

	EVENT_TYPE(MouseButtonRelease)
};
}