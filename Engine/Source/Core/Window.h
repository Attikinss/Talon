#pragma once
#include <string>
#include "Renderer/RenderContext.h"

struct GLFWwindow;

namespace Talon
{
	struct WindowCreateInfo
	{
		RenderContext* Context;
	};

	class Window
	{
	public:
		~Window();

		static Window* Create(const WindowCreateInfo& createInfo);
		void Destroy();

		uint16_t GetWidth() const;
		uint16_t GetHeight() const;
		std::pair<uint16_t, uint16_t> GetSize() const;
		std::pair<float, float> GetPosition() const;
		float GetAspectRatio() const;
		RenderContext& GetContext() const;

	private:
		Window() = default;

	private:
		RenderContext* m_Context = nullptr;
	};
}