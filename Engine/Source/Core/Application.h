#pragma once
#include "Window.h"

namespace Talon
{
	class Application
	{
	public:
		/*Used to create an application instance elsewhere - is defined in Talon's editor application. */
		static Application* Create();

		Application();
		virtual ~Application();

		void Run();

	private:
		Window* m_Window = nullptr;
		bool m_Running = false;
	};
}