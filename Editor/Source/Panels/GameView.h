#pragma once
#include "Viewport.h"

namespace Talon
{
	class GameView : public Viewport
	{
	public:
		GameView(const std::string& name = "Game")
			: Viewport(name)
		{
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

		void Render(Scene& scene) override
		{
			if (s_CurrentCamera)
			{
				m_Framebuffer->Bind();

				scene.Render(*s_CurrentCamera);

				m_Framebuffer->Unbind();
			}
		}

		static void SetCamera(Camera* camera) { s_CurrentCamera = camera; }

	private:
		static inline Camera* s_CurrentCamera = nullptr;
	};
}