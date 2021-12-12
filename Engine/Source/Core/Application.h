#pragma once
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "ECS/EntityRegistry.h"
#include "Window.h"

namespace Talon
{
	class Application
	{
	public:
		/*Used to create an application instance elsewhere - is defined in Talon's editor application.*/
		static Application* Create();

		Application();
		virtual ~Application();

		void Run();
		void ProcessEvents(Event& evt);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() const;

	private:
		bool OnWindowClose(WindowCloseEvent& evt);

	private:
		LayerStack* m_LayerStack = nullptr;
		Window* m_Window = nullptr;
		bool m_Running = false;

		/* Temporary */
		EntityRegistry m_EntityRegistry;
	};
}