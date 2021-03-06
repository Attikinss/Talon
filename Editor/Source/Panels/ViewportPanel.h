#pragma once
#include "EditorPanel.h"
#include <imgui_internal.h>

namespace Talon
{
	class ViewportPanel : public EditorPanel
	{
	public:
		ViewportPanel(const std::string& name)
			: EditorPanel(name)
		{
			
		}

		void Draw(ImGuiWindowFlags additionalFlags = ImGuiWindowFlags_None) override
		{
			if (m_Enabled)
			{
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
				ImGui::Begin(m_Name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | additionalFlags);
				ImGui::GetCurrentContext()->NavWindowingToggleLayer = false;
				bool windowHovered = ImGui::IsWindowHovered();

				if (ImGui::IsMouseClicked(1) && windowHovered)
					ImGui::FocusWindow(ImGui::GetCurrentContext()->CurrentWindow);

				m_Focused = ImGui::IsWindowFocused();
				m_Hovered = ImGui::IsWindowHovered();

				ImVec2 panelSize = ImGui::GetContentRegionAvail();
				m_ViewportSize = { panelSize.x, panelSize.y };
				ImGui::Image(reinterpret_cast<void*>((uint64_t)m_Framebuffer->GetColourAttachment(0)), { m_ViewportSize.x, m_ViewportSize.y }, { 0, 1 }, { 1, 0 });

				ImGui::PopStyleVar();
				ImGui::End();
			}
		}

		void BeginFrame()
		{
			m_Framebuffer->Bind();
		}

		void EndFrame()
		{
			m_Framebuffer->Unbind();
		}

		virtual const Camera& GetCamera() const = 0;

	protected:
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		std::shared_ptr<Framebuffer> m_Framebuffer;
	};
}