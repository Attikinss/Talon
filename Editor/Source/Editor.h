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

	void DrawGUI() override
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N", false, true)) {}
				if (ImGui::MenuItem("Open...", "Ctrl+O", false, true)) {}

				if (ImGui::MenuItem("Save", "Ctrl+S", false, true)) {}
				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S", false, true)) {}
				if (ImGui::MenuItem("Exit", "Ctrl+W")) {}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				if (ImGui::MenuItem("Viewport", "Ctrl+1", false, true)) {}
				if (ImGui::MenuItem("Properties", "Ctrl+2", false, true)) {}
				if (ImGui::MenuItem("Hierarchy", "Ctrl+3", false, true)) {}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("About Talon", "", false, true)) {}
				if (ImGui::MenuItem("Documentation", "", false, true)) {}
				if (ImGui::MenuItem("Release Notes", "", false, true)) {}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

	void Shutdown() override
	{

	}

	void ProcessEvents(Talon::Event& evt) override
	{
		m_EditorCamera.OnEvent(evt);
	}

private:
	Talon::EditorCamera m_EditorCamera;
};