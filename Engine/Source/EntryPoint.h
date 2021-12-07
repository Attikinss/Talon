#pragma once
#include "Core/Application.h"

int main(void)
{
	auto application = Talon::Application::Create();
	application->Run();
	delete application;
	return 0;
}