#pragma once
#include "TalonEngine.h"

class Editor : public Talon::Layer
{
public:
	Editor()
		: Talon::Layer("Editor")
	{

	}

	void Attach() override
	{
		Talon::Logger::Trace("Editor Layer: Attach");
	}

	void Detach() override
	{
		Talon::Logger::Trace("Editor Layer: Detach");
	}

	void Initialise() override
	{
		Talon::Logger::Trace("Editor Layer: Initialise");
	}

	void Update() override
	{
		Talon::Logger::Trace("Editor Layer: Update");
	}

	void Shutdown() override
	{
		Talon::Logger::Trace("Editor Layer: Shutdown");
	}

	void ProcessEvents(Talon::Event& evt) override
	{

	}
};