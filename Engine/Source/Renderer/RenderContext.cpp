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

		// Set up profile and version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, createInfo.ContextVersionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, createInfo.ContextVersionMinor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		int gladStatus = gladLoadGL((GLADloadfunc)glfwGetProcAddress);
		_ASSERT(gladStatus);

		Logger::Trace("Rendering Context created...");
		Logger::Info("OpenGL Info:\n\tVersion: {0}\n\tVendor: {1}\n\tDevice: {2}", glGetString(GL_VERSION), glGetString(GL_VENDOR), glGetString(GL_RENDERER));

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