#pragma once

#include "KeyCode.h"
#include "Events.h"

class KeyEvent : public Event
{
public:

	KeyCode GetKeyCode() const { return m_KeyCode; }

	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

protected:

	KeyEvent(const KeyCode keycode)
		: m_KeyCode(keycode)
	{}

	KeyCode m_KeyCode;

};

class KeyPressedEvent : public KeyEvent
{
public:

	KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
		: KeyEvent(keycode), m_IsRepeat(isRepeat)
	{}

	bool IsRepeat() const { return m_IsRepeat; }

	//EVENT_CLASS_TYPE(KeyPressed)

	static EventType GetStaticType() { return EventType::KeyPressed; }
	virtual EventType GetEventType() const override { return GetStaticType(); }

private:

	bool m_IsRepeat;

};

class KeyReleasedEvent : public KeyEvent
{
public:

	KeyReleasedEvent(const KeyCode keycode)
		: KeyEvent(keycode) 
	{}

	EVENT_CLASS_TYPE(KeyReleased)

};

class KeyTypedEvent : public KeyEvent
{
	KeyTypedEvent(const KeyCode keycode)
		: KeyEvent(keycode) 
	{}

	EVENT_CLASS_TYPE(KeyTyped)
};