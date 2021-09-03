#pragma once
#include "Event.h"

#include <cstdint>
#include <sstream>

namespace DP {
class KeyEvent : public Event {
public:
	inline int keycode() const { return m_keycode; }
	EVENT_CATEGORY(Keyboard | Input)

protected:
	KeyEvent(int32_t keycode)
		: m_keycode(keycode)
	{ }

	int32_t m_keycode;
};

class KeyPressEvent : public KeyEvent {
public:
	KeyPressEvent(int32_t keycode, int32_t repeat_count)
		: KeyEvent(keycode)
		, m_repeat_count(repeat_count)
	{ }

	inline int32_t repeat_count() const { return m_repeat_count; }
	std::string to_str() const override
	{
		std::stringstream ss;
		ss << "[KeyPressEvent] keycode: " << m_keycode << " repeats: " << m_repeat_count;
		return ss.str();
	}

	EVENT_TYPE(KeyPress)

private:
	int32_t m_repeat_count;
};

class KeyReleaseEvent : public KeyEvent {
public:
	KeyReleaseEvent(int32_t keycode)
		: KeyEvent(keycode)
	{ }

	std::string to_str() const override
	{
		std::stringstream ss;
		ss << "[KeyReleaseEvent] keycode: " << m_keycode;
		return ss.str();
	}

	EVENT_TYPE(KeyRelease)
};
}