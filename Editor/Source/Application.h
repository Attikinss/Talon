#pragma once
#define INCLUDE_ENTRY
#include "TalonEngine.h"

#include "Editor.h"

class EditorApplication : public Talon::Application
{
public:
	EditorApplication()
		: Talon::Application()
	{
		PushLayer(new Editor());
	}
};