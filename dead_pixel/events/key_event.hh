#pragma once

#include <core/core.hh>
#include <events/event.hh>

namespace DP {

class KeyEvent : public Event {
public:
	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

	inline int keycode() const { return m_keycode; }
protected:
	KeyEvent(int keycode)
		: m_keycode(keycode)
	{ }

	int m_keycode;
};

class DP_API KeyPressedEvent : public KeyEvent {
public:
	EVENT_CLASS_TYPE(KeyPressed)

	KeyPressedEvent(int keycode, int repeat_count)
		: KeyEvent(keycode)
		, m_repeat_count(repeat_count)
	{ }

	inline int repeat_count() const { return m_repeat_count; }

	virtual std::string to_string() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: keycode = " << m_keycode << "(" << m_repeat_count << "X)";
		return ss.str();
	};
private:
	int m_repeat_count;
};

class DP_API KeyReleasedEvent : public KeyEvent {
public:
	EVENT_CLASS_TYPE(KeyReleased)
	KeyReleasedEvent(int keycode)
		: KeyEvent(keycode)
	{ }

	virtual std::string to_string() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: keycode: " << m_keycode;
		return ss.str();
	}
};

}
