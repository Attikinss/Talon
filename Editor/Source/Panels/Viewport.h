#pragma once
#include "EditorPanel.h"

namespace Talon
{
	class Viewport : public EditorPanel
	{
	public:
		Viewport(const std::string& name = "Viewport") : EditorPanel(name)
		{
			auto [x, y] = Window::Get().GetSize();
			m_ViewportSize = { (float)x, (float)y };

			// Create framebuffer
			FramebufferCreateInfo framebufferCreateInfo;
			framebufferCreateInfo.Width = x;
			framebufferCreateInfo.Height = y;
			framebufferCreateInfo.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH24_STENCIL8 };
			m_Framebuffer = Framebuffer::Create(framebufferCreateInfo);

			m_Cube = m_Registry.CreateEntity();
			auto& meshRenderer = m_Cube.AddComponent<MeshRenderer>();
			meshRenderer.SetMesh(MeshLoader::Load("Assets/Models/cube.obj")[0]);
			meshRenderer.SetMaterial(std::make_shared<Material>(Shader::Create("Assets/Shaders/Basic.glsl")));

			RendererCommand::SetClearColour({ 0.15f, 0.15f, 0.15f, 1.0f });
			RendererCommand::SetFaceCull(true);
			RendererCommand::SetFaceCullType(FaceCullType::Back);
			RendererCommand::SetPrimitiveType(PrimitiveType::Triangles);
			RendererCommand::SetDepthTest(true);
		}

		void Update() override
		{
			FramebufferCreateInfo info = m_Framebuffer->GetInfo();
			if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (info.Width != m_ViewportSize.x || info.Height != m_ViewportSize.y))
			{
				m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
				m_EditorCamera.SetViewSize(m_ViewportSize);
			}

			m_EditorCamera.Update();

			m_Framebuffer->Bind();
			RendererCommand::Clear();
			RendererCommand::BeginFrame(m_EditorCamera);

			m_Cube.GetComponent<MeshRenderer>().Render();

			RendererCommand::EndFrame();
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

		void OnEvent(Event& evt)
		{
			m_EditorCamera.OnEvent(evt);
		}

	private:
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		EditorCamera m_EditorCamera;
		std::shared_ptr<Framebuffer> m_Framebuffer;

		Entity m_Cube;
		EntityRegistry m_Registry;
	};
}