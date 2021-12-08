#include "Window.h"
#include <GLFW/glfw3.h>

namespace Talon
{
	static GLFWwindow* CreateWindowHandle(const char* title, uint16_t width, uint16_t height, bool fullscreen)
	{
		// Initialise glfw if it hasn't been already
		// "Additional calls to this function after successful initialization but before
		// termination will return `GLFW_TRUE` immediately."
		if (!glfwInit())
		{
			// TODO: Freak out
			return nullptr;
		}


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
			windowHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);
		}

		return windowHandle;
	}

	Window* Window::Create(const WindowCreateInfo& createInfo)
	{
		GLFWwindow* windowHandle = CreateWindowHandle(createInfo.Title.c_str(), createInfo.Width, createInfo.Height, createInfo.Fullscreen);

		// Specify render context creation details
		RenderContextCreateInfo contextCreateInfo;
		contextCreateInfo.ContextVersionMajor = 4;
		contextCreateInfo.ContextVersionMinor = 5;
		contextCreateInfo.WindowHandle = windowHandle;

		// Create render context for the window
		Window* window = new Window();
		window->m_Context = RenderContext::Create(contextCreateInfo);

		window->m_WindowHandle = windowHandle;
		window->m_PtrData.Fullscreen = createInfo.Fullscreen;
		window->m_PtrData.Width = createInfo.Width;
		window->m_PtrData.Height = createInfo.Height;
		window->m_PtrData.Title = createInfo.Title;
		window->m_PtrData.VSync = createInfo.VSync;

		// Associate pointer data with the window
		glfwSetWindowUserPointer(window->m_WindowHandle, &window->m_PtrData);

		// Update window size to actual size
		int width, height;
		glfwGetWindowSize(window->m_WindowHandle, &width, &height);
		window->m_PtrData.Width = width;
		window->m_PtrData.Height = height;

		return window;
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Destroy()
	{
		if (m_Context)
		{
			delete m_Context;
			m_Context = nullptr;
		}
	}

	uint16_t Window::GetWidth() const
	{
		return GetSize().first;
	}

	uint16_t Window::GetHeight() const
	{
		return GetSize().second;
	}

	std::pair<uint16_t, uint16_t> Window::GetSize() const
	{
		return GetSize();
	}

	std::pair<float, float> Window::GetPosition() const
	{
		int x, y;
		glfwGetWindowPos(m_WindowHandle, &x, &y);
		return { (float)x, (float)y };
	}

	float Window::GetAspectRatio() const
	{
		auto [x, y] = GetSize();
		return (float)x / y;
	}

	RenderContext& Window::GetContext() const
	{
		return *m_Context;
	}

	bool Window::VSyncEnabled() const
	{
		return m_PtrData.VSync;
	}

	GLFWwindow* Window::GetWindowHandle() const
	{
		return m_WindowHandle;
	}
}