#pragma once
#include "ViewportPanel.h"

namespace Talon
{
	class GameViewPanel : public ViewportPanel
	{
	public:
		GameViewPanel() : ViewportPanel("Details") { }
		GameViewPanel(const std::shared_ptr<Scene>& scene)
			: ViewportPanel("Game")
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

				// TODO: Resize according to a set resolution/aspect ratio
				if (s_CurrentCamera)
					s_CurrentCamera->SetViewSize(m_ViewportSize);
			}
		}

		void OnEvent(Event& evt) override
		{

		}

		const Camera& GetCamera() const override { return *s_CurrentCamera; }

		static void SetCamera(Camera* camera) { s_CurrentCamera = camera; }

	private:
		static inline Camera* s_CurrentCamera = nullptr;
	};
}