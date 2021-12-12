#pragma once
#include "Event.h"

namespace Talon
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		std::pair<float, float> GetPosition() const { return { m_MouseX, m_MouseY }; }

		static EventType GetStaticType() { return EventType::MouseMoved; }
		EventType GetEventType() const override { return GetStaticType(); }
		int GetCategoryFlags() const override { return EventCategory::CategoryMouse | EventCategory::CategoryInput; }
		const char* GetName() const override { return RAW(MouseMoved); }

		std::string ToString() const override
		{
			std::ostringstream stream;
			stream << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return stream.str();
		}

	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : m_OffsetX(xOffset), m_OffsetY(yOffset) {}

		std::pair<float, float> GetOffset() const { return { m_OffsetX, m_OffsetY }; }

		static EventType GetStaticType() { return EventType::MouseScrolled; }
		EventType GetEventType() const override { return GetStaticType(); }
		int GetCategoryFlags() const override { return EventCategory::CategoryMouse | EventCategory::CategoryInput; }
		const char* GetName() const override { return RAW(MouseScrolled); }

		std::string ToString() const override
		{
			std::ostringstream stream;
			stream << "MouseScrolledEvent: " << m_OffsetX << ", " << m_OffsetY;
			return stream.str();
		}

	private:
		float m_OffsetX, m_OffsetY;
	};

	class MouseButtonEvent : public Event
	{
	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {}

	public:
		int GetMouseButton() const { return m_Button; }
		int GetCategoryFlags() const override { return EventCategory::CategoryMouse | EventCategory::CategoryInput | EventCategory::CategoryMouseButton; }

	protected:
		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		static EventType GetStaticType() { return EventType::MousePressed; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return RAW(MousePressed); }

		std::string ToString() const override
		{
			std::ostringstream stream;
			stream << "MouseButtonPressedEvent: " << m_Button;
			return stream.str();
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		static EventType GetStaticType() { return EventType::MouseReleased; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return RAW(MouseReleased); }

		std::string ToString() const override
		{
			std::ostringstream stream;
			stream << "MouseButtonReleasedEvent: " << m_Button;
			return stream.str();
		}
	};
}