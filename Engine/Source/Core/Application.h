#pragma once
#include "LayerStack.h"
#include "Window.h"

#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

namespace Talon
{
	class Application
	{
	public:
		/*Used to create an application instance elsewhere - is defined in Talon's editor application.*/
		static Application* Create();

		Application();
		virtual ~Application() = default;

		void Run();
		void ProcessEvents(Event& evt);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() const;

	private:
		void OnStartUp();
		void OnShutDown();

		bool OnWindowClose(WindowCloseEvent& evt);

	private:
		LayerStack* m_LayerStack = nullptr;
		ImGuiLayer* m_GUILayer = nullptr;
		Window* m_Window = nullptr;
		bool m_Running = false;
	};
}