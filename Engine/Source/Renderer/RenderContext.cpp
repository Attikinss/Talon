#include "RenderContext.h"

#include <GLFW/glfw3.h>

namespace Talon
{
	static RenderContext* s_Current = nullptr;

	static GLFWwindow* CreateWindowHandle(const char* title, uint16_t width, uint16_t height, bool fullscreen)
	{
		// Create the window
		GLFWwindow* windowHandle = nullptr;
		if (fullscreen)
		{
			// Query the primary monitor and its current state
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			// Create the window in fullscreen mode
			windowHandle = glfwCreateWindow(mode->width, mode->height, title, monitor, nullptr);
		}
		else
		{
			// Create the window in non-fullscreen mode
			windowHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);		}

		return windowHandle;
	}

	RenderContext* RenderContext::Create(const RenderContextCreateInfo& createInfo, bool makeCurrent)
	{
		// Initialise glfw if it hasn't been already
		// "Additional calls to this function after successful initialization but before
		// termination will return `GLFW_TRUE` immediately."
		if (!glfwInit())
		{
			// TODO: Freak out
			return nullptr;
		}

		// Set up profile and version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, createInfo.ContextVersionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, createInfo.ContextVersionMinor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		RenderContext* context = new RenderContext();
		context->m_WindowHandle = CreateWindowHandle(createInfo.Title.c_str(), createInfo.Width, createInfo.Height, createInfo.Fullscreen);

		context->m_PtrData.Fullscreen = createInfo.Fullscreen;
		context->m_PtrData.Width = createInfo.Width;
		context->m_PtrData.Height = createInfo.Height;
		context->m_PtrData.Title = createInfo.Title;
		context->m_PtrData.VSync = createInfo.VSync;

		// Bail if window fails to create
		if (!context->ValidState())
		{
			// TODO: Freak out
			return nullptr;
		}

		// Associate pointer data with the window
		glfwSetWindowUserPointer(context->m_WindowHandle, &context->m_PtrData);

		// Update window size to actual size
		int width, height;
		glfwGetWindowSize(context->m_WindowHandle, &width, &height);
		context->m_PtrData.Width = width;
		context->m_PtrData.Height = height;

		// Context current if specified
		if (makeCurrent)
		{
			s_Current = context;
			glfwMakeContextCurrent(context->m_WindowHandle);
		}

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

	bool RenderContext::VSyncEnabled() const
	{
		return m_PtrData.VSync;
	}

	std::pair<uint16_t, uint16_t> RenderContext::GetSize() const
	{
		return { m_PtrData.Width, m_PtrData.Height };
	}

	std::pair<float, float> RenderContext::GetPosition() const
	{
		int x, y;
		glfwGetWindowPos(m_WindowHandle, &x, &y);
		return { (float)x, (float)y };
	}

	GLFWwindow* RenderContext::GetWindowHandle() const
	{
		return m_WindowHandle;
	}

	bool RenderContext::ValidState()
	{
		return m_WindowHandle != nullptr;
	}
}