#include "Application.h"

namespace Talon
{
	Application::Application()
	{
		// Specify render context creation details
		RenderContextCreateInfo contextCreateInfo;
		contextCreateInfo.ContextVersionMajor = 4;
		contextCreateInfo.ContextVersionMinor = 5;
		contextCreateInfo.Fullscreen = false;
		contextCreateInfo.Width = 1280;
		contextCreateInfo.Height = 720;
		contextCreateInfo.Title = "Talon";
		contextCreateInfo.VSync = true;

		RenderContext* context = RenderContext::Create(contextCreateInfo, true);

		// Specify window creation details
		WindowCreateInfo winCreateInfo;
		winCreateInfo.Context = context;

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