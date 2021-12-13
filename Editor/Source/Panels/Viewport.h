#pragma once
#include "EditorPanel.h"

class Viewport : public EditorPanel
{
public:
	Viewport() : EditorPanel("Viewport")
	{
		auto [x, y] = Talon::Window::Get().GetSize();
		m_ViewportSize = { (float)x, (float)y };
	}

	void Update() override
	{
		m_EditorCamera.Update();

		Talon::RendererCommand::Clear(0.15f, 0.15f, 0.15f);
		Talon::RendererCommand::BeginFrame(m_EditorCamera);

		Talon::RendererCommand::EndFrame();
	}

	void Draw() override
	{
		if (m_Enabled)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin(m_Name.c_str(), &m_Enabled, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

			ImVec2 panelSize = ImGui::GetContentRegionAvail();
			m_ViewportSize = { panelSize.x, panelSize.y };

			ImGui::PopStyleVar();
			ImGui::End();
		}
	}

	void OnEvent(Talon::Event& evt)
	{
		m_EditorCamera.OnEvent(evt);
	}

private:
	glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
	Talon::EditorCamera m_EditorCamera;
};