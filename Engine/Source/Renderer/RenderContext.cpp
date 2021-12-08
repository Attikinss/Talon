#include "RenderContext.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Talon
{
	static RenderContext* s_Current = nullptr;

	RenderContext* RenderContext::Create(const RenderContextCreateInfo& createInfo)
	{
		RenderContext* context = new RenderContext();
		context->m_WindowHandle = createInfo.WindowHandle;

		// Set up profile and version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, createInfo.ContextVersionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, createInfo.ContextVersionMinor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		int gladStatus = gladLoadGL((GLADloadfunc)glfwGetProcAddress);
		_ASSERT((gladStatus == 0));

		// TODO: Do GPU info dump here

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