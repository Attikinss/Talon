#pragma once
#include <string>
#include "Renderer/RenderContext.h"
#include "Events/Event.h"

struct GLFWwindow;

namespace Talon
{
	struct WindowCreateInfo
	{
		std::string Title = std::string();
		uint16_t Width = 0, Height = 0;
		bool Fullscreen = false;
		bool VSync = false;
	};

	class Window
	{
	private:
		struct WindowPtrData
		{
			std::string Title = std::string();
			uint16_t Width = 0, Height = 0;
			bool Fullscreen = false;
			bool VSync = false;

			EventCallback Callback = EventCallback();
		};

	public:
		~Window();

		static Window* Create(const WindowCreateInfo& createInfo);
		void Destroy();

		void SetEventCallback(const EventCallback& callback) { m_PtrData.Callback = callback; }

		bool VSyncEnabled() const;
		uint16_t GetWidth() const;
		uint16_t GetHeight() const;
		std::pair<uint16_t, uint16_t> GetSize() const;
		std::pair<float, float> GetPosition() const;
		float GetAspectRatio() const;
		GLFWwindow* GetWindowHandle() const;
		RenderContext& GetContext() const;

		static Window& Get() { return *s_Instance; }

	private:
		Window() = default;
		void SetCallbacks();

	private:
		WindowPtrData m_PtrData;

		GLFWwindow* m_WindowHandle = nullptr;
		RenderContext* m_Context = nullptr;

		static Window* s_Instance;
	};
}