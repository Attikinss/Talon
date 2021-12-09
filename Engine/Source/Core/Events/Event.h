#pragma once
#include "Core/Defines.h"
#include <functional>
#include <sstream>
#include <string>

namespace Talon
{
	class Event;
	using EventCallback = std::function<void(Event&)>;

	enum EventType
	{
		TypeNone = 0,
		WindowClose, WindowResize, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MousePressed, MouseReleased, MouseMoved, MouseScrolled,
		FileDrop,
	};

	enum EventCategory
	{
		CategoryNone = 0,
		CategoryApplication	= BIT(0),
		CategoryInput		= BIT(1),
		CategoryKeyboard	= BIT(2),
		CategoryMouse		= BIT(3),
		CategoryMouseButton	= BIT(4)
	};

	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

	public:
		bool m_Used = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& evt)
			: m_Event(evt) {}

		template<typename T>
		bool Dispatch(const EventFunc<T>& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// Execute the function and mark as handled
				// if the event is blocked for further use
				m_Event.m_Used |= func(static_cast<T&>(m_Event));
				return true;
			}

			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& stream, const Event& evt)
	{
		return stream << evt.ToString();
	}
}