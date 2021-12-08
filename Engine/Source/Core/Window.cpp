#include "Window.h"
#include "Logger.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"

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
			Logger::Critical("Failed to initialise GLFW!");
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

		if (windowHandle)
			Logger::Trace("Window Created...");
		else
			Logger::Critical("Failed to create window!");

		return windowHandle;
	}

	Window* Window::Create(const WindowCreateInfo& createInfo)
	{
		GLFWwindow* windowHandle = CreateWindowHandle(createInfo.Title.c_str(), createInfo.Width, createInfo.Height, createInfo.Fullscreen);
		glfwMakeContextCurrent(windowHandle);

		// Specify render context creation details
		RenderContextCreateInfo contextCreateInfo;
		contextCreateInfo.ContextVersionMajor = 4;
		contextCreateInfo.ContextVersionMinor = 5;
		contextCreateInfo.WindowHandle = windowHandle;

		// Create render context for the window
		Window* window = new Window();
		window->m_Context = RenderContext::Create(contextCreateInfo);
		window->m_Context->MakeCurrent();

		window->m_WindowHandle = windowHandle;
		window->m_PtrData.Fullscreen = createInfo.Fullscreen;
		window->m_PtrData.Width = createInfo.Width;
		window->m_PtrData.Height = createInfo.Height;
		window->m_PtrData.Title = createInfo.Title;
		window->m_PtrData.VSync = createInfo.VSync;

		// Associate pointer data with the window
		glfwSetWindowUserPointer(window->m_WindowHandle, &window->m_PtrData);

		window->SetCallbacks();

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

	void Window::SetCallbacks()
	{
		// Window resizing callback
		glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* window, int width, int height)
			{
				auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));

				WindowResizeEvent event((uint32_t)width, (uint32_t)height);
				data.Callback(event);
				data.Width = width;
				data.Height = height;
			});

		// Window closing callback
		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window)
			{
				auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));

				WindowCloseEvent event;
				data.Callback(event);
			});

		// Key interaction callack
		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.Callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.Callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.Callback(event);
					break;
				}
				}
			});

		// Character type cllback
		glfwSetCharCallback(m_WindowHandle, [](GLFWwindow* window, uint32_t keycode)
			{
				auto& data = *(WindowPtrData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent typed(keycode);
				data.Callback(typed);
			});

		// Mouse button interaction callback
		glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* window, int button, int action, int mods)
			{
				auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.Callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.Callback(event);
					break;
				}
				}
			});

		// Mouse scroll wheel callback
		glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.Callback(event);
			});

		// Mouse move callback
		glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, double x, double y)
			{
				auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));
				MouseMovedEvent event((float)x, (float)y);
				data.Callback(event);
			});
	}
}