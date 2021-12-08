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

		m_LayerStack = new LayerStack();

		m_Running = true;
	}

	Application::~Application()
	{
		delete m_LayerStack;
		delete m_Window;
	}

	void Application::Run()
	{
		for (Layer* layer : *m_LayerStack)
			layer->Initialise();

		while (m_Running)
		{
			m_Window->GetContext().ProcessEvents();

			// Update all layers
			for (Layer* layer : *m_LayerStack)
				layer->Update();

			m_Window->GetContext().SwapBuffers();
		}
	}

	void Application::ProcessEvents(Event& evt)
	{
		EventDispatcher dispatcher(evt);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FUNCTION(Application::OnWindowClose));

		// Iterate back to front passing the event to each layer
		for (auto it = m_LayerStack->rend(); it != m_LayerStack->rbegin();)
		{
			// Bail once the event has been handled
			if (evt.m_Used)
				break;

			// Process the event on the current layer
			(*--it)->ProcessEvents(evt);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack->PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack->PushOverlay(layer);
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