#pragma once

#include <functional>

enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
	None = 0,
	EventCategoryApplication,
	EventCategoryInput,
	EventCategoryKeyboard,
	EventCategoryMouse,
	EventCategoryMouseButton
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\

#define EVENT_CLASS_CATEGORY(category) virtual int GetEventCategory() const override { return category; }


class Event
{
public:

	virtual ~Event() = default;

	bool m_Handled = false;

	virtual EventType GetEventType() const = 0;

	virtual int GetEventCategory() const = 0;

	bool IsInCategory(EventCategory category)
	{
		return GetEventCategory() & category;
	}

};

class EventDispatcher
{
public:

	EventDispatcher(Event& event)
		:m_Event(event)
	{}

	template<typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.m_Handled |= func(static_cast<T&>(m_Event));
			return true;
		}
		return false;
	}

private:

	Event& m_Event;

};