#include "Application.h"

#include <stdlib.h>
#include <iostream>

namespace Talon
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		printf("Hello, World!");

		while (m_Running);
	}
}