#pragma once
#include "ViewportPanel.h"

namespace Talon
{
	class SceneViewPanel : public ViewportPanel
	{
	public:
		SceneViewPanel() : ViewportPanel("Details") { }
		SceneViewPanel(const std::shared_ptr<Scene>& scene)
			: ViewportPanel("Scene")
		{
			SetScene(scene);

			auto [x, y] = Window::Get().GetSize();
			m_ViewportSize = { (float)x, (float)y };

			// Create framebuffer
			FramebufferCreateInfo framebufferCreateInfo;
			framebufferCreateInfo.Width = x;
			framebufferCreateInfo.Height = y;
			framebufferCreateInfo.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH24_STENCIL8 };
			m_Framebuffer = Framebuffer::Create(framebufferCreateInfo);
		}

		void Update() override
		{
			FramebufferCreateInfo info = m_Framebuffer->GetInfo();
			if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (info.Width != m_ViewportSize.x || info.Height != m_ViewportSize.y))
			{
				m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
				m_EditorCamera.SetViewSize(m_ViewportSize);
			}

			m_EditorCamera.Update(m_Focused);
		}

		void Draw(ImGuiWindowFlags additionalFlags = ImGuiWindowFlags_None) override
		{
			ViewportPanel::Draw();


		}

		void OnEvent(Event& evt)
		{
			if (m_Hovered)
				m_EditorCamera.OnEvent(evt);
		}

		const Camera& GetCamera() const override { return m_EditorCamera; }

	private:
		EditorCamera m_EditorCamera;
	};
}