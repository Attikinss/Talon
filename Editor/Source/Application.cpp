#include "Application.h"

namespace Talon
{
	Application* Application::Create()
	{
		return new EditorApplication();
	}
}