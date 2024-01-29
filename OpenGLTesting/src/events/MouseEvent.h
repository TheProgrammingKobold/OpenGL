#pragma once

#include "Events.h"
#include "MouseCodes.h"

class MouseMovedEvent : public Event
{
public:

	MouseMovedEvent(const float x, const float y)
		: m_MouseX(x), m_MouseY(y)
	{}

	float GetX() const { return m_MouseX; }
	float GetY() const { return m_MouseY; }

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:

	float m_MouseX, m_MouseY;

};

class MouseScrolledEvent : public Event
{
public:

	MouseScrolledEvent(const float xOffset, const float yOffset)
		:m_xOffset(xOffset), m_yOffset(yOffset)
	{}

	float GetXOffset() const { return m_xOffset; }
	float GetYOffset() const { return m_yOffset; }

	EVENT_CLASS_TYPE(MouseScrolled)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:

	float m_xOffset, m_yOffset;

};

class MouseButtonEvent : public Event
{
public:

	MouseCode GetMouseButton() const { return m_Button; }

	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

protected:

	MouseButtonEvent(const MouseCode button)
		: m_Button(button)
	{}

	MouseCode m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:

	MouseButtonPressedEvent(const MouseCode button)
		: MouseButtonEvent(button)
	{}

	EVENT_CLASS_TYPE(MouseButtonPressed)

};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:

	MouseButtonReleasedEvent(const MouseCode button)
		: MouseButtonEvent(button)
	{}

	EVENT_CLASS_TYPE(MouseButtonReleased)
};