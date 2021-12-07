#include "Application.h"

Talon::Application* Talon::Application::Create()
{
	return new Application();
}