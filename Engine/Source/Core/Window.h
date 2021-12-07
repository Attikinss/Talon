#pragma once
#include <string>

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
		virtual ~Window() = default;

		static Window* Create(const WindowCreateInfo& createInfo);
		void Destroy();

		/* Temporary */
		void ProcessEvents();
		void SwapBuffers();
		bool ShouldClose();

		bool VSyncEnabled() const;
		uint16_t GetWidth() const;
		uint16_t GetHeight() const;
		std::pair<uint16_t, uint16_t> GetSize() const;
		std::pair<float, float> GetPosition() const;
		float GetAspectRatio() const;
		void* GetWindowHandle() const;

	private:
		Window() = default;

	private:
		GLFWwindow* m_WindowHandle = nullptr;
		WindowPtrData m_PtrData;
	};
}