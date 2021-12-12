#include "Application.h"
#include "Defines.h"
#include "Logger.h"

#include "ECS/Entity.h"
#include "ECS/WorldCamera.h"

#include "Renderer/Renderer.h"
#include "Renderer/RendererCommand.h"

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

		Renderer::Initialise();

		m_LayerStack = new LayerStack();

		m_Running = true;
	}

	Application::~Application()
	{
		Renderer::Shutdown();

		delete m_LayerStack;
		delete m_Window;
	}

	void Application::Run()
	{
		// TODO: Make Enities shared pointers?
		Entity cameraEntity = m_EntityRegistry.CreateEntity();
		WorldCamera& camera = cameraEntity.AddComponent<WorldCamera>();
		camera.SetPosition({ 0.0f, 0.0f, 1.0f });

		for (Layer* layer : *m_LayerStack)
			layer->Initialise();

		while (m_Running)
		{
			m_Window->GetContext().ProcessEvents();

			RendererCommand::Clear(0.15f, 0.15f, 0.15f);
			RendererCommand::BeginFrame(cameraEntity.GetComponent<WorldCamera>());

			// Update all layers
			for (Layer* layer : *m_LayerStack)
				layer->Update();

			RendererCommand::EndFrame();

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