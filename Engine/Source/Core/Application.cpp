#include "Application.h"
#include "Logger.h"

#include "Defines.h"

#include "Events/ApplicationEvent.h"

namespace Talon
{
	Application::Application()
	{
		Logger::Initialise();

		// Specify window creation details
		WindowCreateInfo winCreateInfo;
		winCreateInfo.Fullscreen = false;
		winCreateInfo.Width = 1280;
		winCreateInfo.Height = 720;
		winCreateInfo.Title = "Talon";
		winCreateInfo.VSync = true;

		m_Window = Window::Create(winCreateInfo);
		m_Window->SetEventCallback(BIND_FUNCTION(Application::ProcessEvents));

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

	void Application::ProcessEvents(Event& evt)
	{
		EventDispatcher dispatcher(evt);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FUNCTION(Application::OnWindowClose));
	}

	Window& Application::GetWindow() const
	{
		return *m_Window;
	}

	bool Application::OnWindowClose(WindowCloseEvent& evt)
	{
		m_Running = false;
		return false;
	}
}