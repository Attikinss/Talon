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

	}

	void Detach() override
	{

	}

	void Initialise() override
	{

	}

	void Update() override
	{
		m_EditorCamera.Update();

		Talon::RendererCommand::Clear(0.15f, 0.15f, 0.15f);
		Talon::RendererCommand::BeginFrame(m_EditorCamera);

		Talon::RendererCommand::EndFrame();
	}

	void Shutdown() override
	{

	}

	void ProcessEvents(Talon::Event& evt) override
	{

	}

private:
	Talon::EditorCamera m_EditorCamera;
};