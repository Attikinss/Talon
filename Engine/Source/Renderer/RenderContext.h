#pragma once
#include <string>

struct GLFWwindow;

namespace Talon
{
	struct RenderContextCreateInfo
	{
		GLFWwindow* WindowHandle;
	};

	class RenderContext
	{
	public:
		static RenderContext* Create(const RenderContextCreateInfo& createInfo);
		static RenderContext* Current();
		~RenderContext();

		void MakeCurrent();
		void ProcessEvents();
		void SwapBuffers();

	private:
		RenderContext() = default;
		bool ValidState();

	private:
		GLFWwindow* m_WindowHandle = nullptr;
	};
}