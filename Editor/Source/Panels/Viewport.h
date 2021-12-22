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

			m_Light = m_CurrentScene.CreateEntity();
			m_Light.GetComponent<Transform>().Rotation = glm::quatLookAt(glm::normalize(glm::vec3(-1.5f, -2.0f, -2.5f)), { 0.0f, 1.0f, 0.0f });

			m_TestMaterial = std::make_shared<Material>(Shader::Create("Assets/Shaders/DefaultLit.glsl"));

			m_Cube = m_CurrentScene.CreateEntity();
			auto& meshRenderer = m_Cube.AddComponent<MeshRenderer>();
			meshRenderer.SetMesh(MeshLoader::Load("Assets/Models/cube.obj")[0]);
			meshRenderer.SetMaterial(m_TestMaterial);

			m_CubeAlbedo = Texture2D::Create("Assets/Textures/greasy-pan-2-albedo.png");
			m_CubeNormal = Texture2D::Create("Assets/Textures/greasy-pan-2-normal.png");

			m_TestMaterial->Bind();
			m_TestMaterial->SetInt("u_AlbedoTex", 0);
			m_TestMaterial->SetInt("u_NormalTex", 1);

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

			m_CurrentScene.Update();
			m_EditorCamera.Update();

			m_CubeAlbedo->Bind(0);
			m_CubeNormal->Bind(1);

			m_TestMaterial->Bind();

			m_TestMaterial->SetVector3("u_LightDirection", m_Light.GetComponent<Transform>().Forward);
			m_TestMaterial->SetVector3("u_LightPosition", { -0.75f, -1.5f, -2.5f });
			m_TestMaterial->SetVector3("u_Attenuation", { 1.0f, 0.01f, 0.002f });

			// TODO: Add to lighting uniform buffer
			m_TestMaterial->SetVector3("u_AmbientLightColour", glm::vec3(0.1f));

			m_Framebuffer->Bind();
			RendererCommand::Clear();
			RendererCommand::BeginFrame(m_EditorCamera);

			RendererCommand::Submit(m_Cube.GetComponent<MeshRenderer>(), m_Cube.GetComponent<Transform>().GetTransform());

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
		Entity m_Light;
		Scene m_CurrentScene;
		std::shared_ptr<Material> m_TestMaterial;

		std::shared_ptr<Texture2D> m_CubeAlbedo;
		std::shared_ptr<Texture2D> m_CubeNormal;
	};
}