#pragma once
#include <string>

struct GLFWwindow;

namespace Talon
{
	struct RenderContextCreateInfo
	{
		int ContextVersionMajor;
		int ContextVersionMinor;

		bool Fullscreen;
		uint16_t Width, Height;
		std::string Title;
		bool VSync;
	};

	class RenderContext
	{
	private:
		struct ContextPtrData
		{
			std::string Title;
			uint16_t Width, Height;
			bool Fullscreen;
			bool VSync;
		};

	public:
		static RenderContext* Create(const RenderContextCreateInfo& createInfo, bool makeCurrent);
		static RenderContext* Current();
		~RenderContext();

		void MakeCurrent();
		void ProcessEvents();
		void SwapBuffers();

		bool VSyncEnabled() const;
		std::pair<uint16_t, uint16_t> GetSize() const;
		std::pair<float, float> GetPosition() const;
		GLFWwindow* GetWindowHandle() const;

	private:
		RenderContext() = default;
		bool ValidState();

	private:
		GLFWwindow* m_WindowHandle = nullptr;
		ContextPtrData m_PtrData;
	};
}