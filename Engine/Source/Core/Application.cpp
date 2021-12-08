#include "Application.h"

namespace Talon
{
	Application::Application()
	{
		// Specify window creation details
		WindowCreateInfo winCreateInfo;
		winCreateInfo.Fullscreen = false;
		winCreateInfo.Width = 1280;
		winCreateInfo.Height = 720;
		winCreateInfo.Title = "Talon";
		winCreateInfo.VSync = true;

		m_Window = Window::Create(winCreateInfo);

		m_Running = true;
	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->GetContext().ProcessEvents();

			m_Window->GetContext().SwapBuffers();
		}
	}

	Window& Application::GetWindow() const
	{
		return *m_Window;
	}
}