#include "Application.h"

namespace Talon
{
	Application::Application()
	{
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
			m_Running = !m_Window->ShouldClose();

			m_Window->ProcessEvents();

			m_Window->SwapBuffers();
		}
	}
}