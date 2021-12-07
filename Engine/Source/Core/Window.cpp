#include "Window.h"

#include <GLFW/glfw3.h>

namespace Talon
{
	Window* Window::Create(const WindowCreateInfo& createInfo)
	{
		Window* window = new Window();

		window->m_PtrData.Fullscreen = createInfo.Fullscreen;
		window->m_PtrData.Width = createInfo.Width;
		window->m_PtrData.Height = createInfo.Height;
		window->m_PtrData.Title = createInfo.Title;
		window->m_PtrData.VSync = createInfo.VSync;

		// Initialise glfw 
		if (!glfwInit())
		{
			// TODO: Freak out
			return nullptr;
		}

		// Set up the correct profile and version
		// TODO: Store this information in a CreateContextInfo type struct
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create the window
		if (createInfo.Fullscreen)
		{
			// Query the primary monitor and its current state
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			// Create the window in fullscreen mode
			window->m_WindowHandle = glfwCreateWindow(mode->width, mode->height, createInfo.Title.c_str(), monitor, nullptr);
		}
		else
		{
			// Create the window in non-fullscreen mode
			window->m_WindowHandle = glfwCreateWindow((int)createInfo.Width, (int)createInfo.Height, createInfo.Title.c_str(), nullptr, nullptr);
		}

		// Bail if window fails to create
		if (!window->m_WindowHandle)
		{
			// TODO: Freak out
			window->Destroy();
		}

		// Associate pointer data with the window
		glfwSetWindowUserPointer(window->m_WindowHandle, &window->m_PtrData);

		// Update window size to actual size
		int width, height;
		glfwGetWindowSize(window->m_WindowHandle, &width, &height);
		window->m_PtrData.Width = width;
		window->m_PtrData.Height = height;

		return window;
	}

	void Window::Destroy()
	{
		if (m_WindowHandle)
			glfwDestroyWindow(m_WindowHandle);
		
		glfwTerminate();
	}

	void Window::ProcessEvents()
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(m_WindowHandle);
	}

	bool Window::VSyncEnabled() const
	{
		return m_PtrData.VSync;
	}

	uint16_t Window::GetWidth() const
	{
		return m_PtrData.Width;
	}

	uint16_t Window::GetHeight() const
	{
		return m_PtrData.Height;
	}

	std::pair<uint16_t, uint16_t> Window::GetSize() const
	{
		return { m_PtrData.Width, m_PtrData.Height };
	}

	std::pair<float, float> Window::GetPosition() const
	{
		int x, y;
		glfwGetWindowPos(m_WindowHandle, &x, &y);
		return { (float)x, (float)y };
	}

	float Window::GetAspectRatio() const
	{
		return (float)m_PtrData.Width / m_PtrData.Height;
	}

	void* Window::GetWindowHandle() const
	{
		return m_WindowHandle;
	}
}