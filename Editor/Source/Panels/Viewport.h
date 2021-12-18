#pragma once
#include "EditorPanel.h"

#include <imgui_internal.h>

class Viewport : public EditorPanel
{
public:
	Viewport(const std::string& name = "Viewport") : EditorPanel(name)
	{
		auto [x, y] = Talon::Window::Get().GetSize();
		m_ViewportSize = { (float)x, (float)y };

		// Create framebuffer
		Talon::FramebufferCreateInfo framebufferCreateInfo;
		framebufferCreateInfo.Width = x;
		framebufferCreateInfo.Height = y;
		framebufferCreateInfo.Attachments = { Talon::FramebufferTextureFormat::RGBA8, Talon::FramebufferTextureFormat::DEPTH24_STENCIL8 };
		m_Framebuffer = Talon::Framebuffer::Create(framebufferCreateInfo);

		m_Cube = m_Registry.CreateEntity();
		auto& meshRenderer = m_Cube.AddComponent<Talon::MeshRenderer>();
		meshRenderer.SetMesh(Talon::MeshLoader::Load("Assets/Models/cube.obj")[0]);

		Talon::RendererCommand::SetFaceCull(true);
		Talon::RendererCommand::SetFaceCullType(Talon::FaceCullType::Back);
		Talon::RendererCommand::SetPrimitiveType(Talon::PrimitiveType::Triangles);
		Talon::RendererCommand::SetDepthTest(true);
	}

	void Update() override
	{
		Talon::FramebufferCreateInfo info = m_Framebuffer->GetInfo();
		if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (info.Width != m_ViewportSize.x || info.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_EditorCamera.SetViewSize(m_ViewportSize);
		}

		m_EditorCamera.Update();

		m_Framebuffer->Bind();
		Talon::RendererCommand::Clear();
		Talon::RendererCommand::BeginFrame(m_EditorCamera);

		m_Cube.GetComponent<Talon::MeshRenderer>().Render();

		Talon::RendererCommand::EndFrame();
		m_Framebuffer->Unbind();
	}

	void Draw(ImGuiWindowFlags_ additionalFlags) override
	{
		if (m_Enabled)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin(m_Name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | additionalFlags);

			ImVec2 panelSize = ImGui::GetContentRegionAvail();
			m_ViewportSize = { panelSize.x, panelSize.y };
			ImGui::Image(reinterpret_cast<void*>((uint64_t)m_Framebuffer->GetColourAttachment(0)), { m_ViewportSize.x, m_ViewportSize.y }, { 0, 1 }, { 1, 0 });

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
	std::shared_ptr<Talon::Framebuffer> m_Framebuffer;

	Talon::Entity m_Cube;
	Talon::EntityRegistry m_Registry;
};