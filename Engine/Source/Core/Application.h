#pragma once
#include "Window.h"
#include "Events/ApplicationEvent.h"

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

		Window& GetWindow() const;

	private:
		bool OnWindowClose(WindowCloseEvent& evt);

	private:
		Window* m_Window = nullptr;
		bool m_Running = false;
	};
}