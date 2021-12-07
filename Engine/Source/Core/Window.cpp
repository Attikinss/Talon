#include "Window.h"

namespace Talon
{
	Window* Window::Create(const WindowCreateInfo& createInfo)
	{
		Window* window = new Window();
		window->m_Context = createInfo.Context;

		return window;
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Destroy()
	{
		if (m_Context)
		{
			delete m_Context;
			m_Context = nullptr;
		}
	}

	uint16_t Window::GetWidth() const
	{
		return m_Context->GetSize().first;
	}

	uint16_t Window::GetHeight() const
	{
		return m_Context->GetSize().second;
	}

	std::pair<uint16_t, uint16_t> Window::GetSize() const
	{
		return m_Context->GetSize();
	}

	std::pair<float, float> Window::GetPosition() const
	{
		return m_Context->GetPosition();
	}

	float Window::GetAspectRatio() const
	{
		auto [x, y] = m_Context->GetSize();
		return (float)x / y;
	}

	RenderContext& Window::GetContext() const
	{
		return *m_Context;
	}
}