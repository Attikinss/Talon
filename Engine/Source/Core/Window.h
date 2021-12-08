#pragma once
#include <string>
#include "Renderer/RenderContext.h"

struct GLFWwindow;

namespace Talon
{
	struct WindowCreateInfo
	{
		std::string Title;
		uint16_t Width, Height;
		bool Fullscreen;
		bool VSync;
	};

	class Window
	{
	private:
		struct WindowPtrData
		{
			std::string Title;
			uint16_t Width, Height;
			bool Fullscreen;
			bool VSync;
		};

	public:
		~Window();

		static Window* Create(const WindowCreateInfo& createInfo);
		void Destroy();

		bool VSyncEnabled() const;
		uint16_t GetWidth() const;
		uint16_t GetHeight() const;
		std::pair<uint16_t, uint16_t> GetSize() const;
		std::pair<float, float> GetPosition() const;
		float GetAspectRatio() const;
		GLFWwindow* GetWindowHandle() const;
		RenderContext& GetContext() const;

	private:
		Window() = default;

	private:
		WindowPtrData m_PtrData;

		GLFWwindow* m_WindowHandle = nullptr;
		RenderContext* m_Context = nullptr;
	};
}