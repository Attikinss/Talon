#include "RenderContext.h"
#include "Core/Logger.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Talon
{
	static RenderContext* s_Current = nullptr;

	RenderContext* RenderContext::Create(const RenderContextCreateInfo& createInfo)
	{
		RenderContext* context = new RenderContext();
		context->m_WindowHandle = createInfo.WindowHandle;

		Logger::Trace("Rendering Context created...");

		return context;
	}

	RenderContext* RenderContext::Current()
	{
		return s_Current;
	}

	RenderContext::~RenderContext()
	{
		if (s_Current == this)
			s_Current = nullptr;

		glfwDestroyWindow(m_WindowHandle);
		m_WindowHandle = nullptr;
	}

	void RenderContext::MakeCurrent()
	{
		s_Current = this;
		glfwMakeContextCurrent(m_WindowHandle);
	}

	void RenderContext::ProcessEvents()
	{
		glfwPollEvents();
	}

	void RenderContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	bool RenderContext::ValidState()
	{
		return m_WindowHandle != nullptr;
	}
}