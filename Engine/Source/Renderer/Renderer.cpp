#include "Renderer.h"

#include "Core/Logger.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Talon
{
	static bool s_Initialised = false;

	static bool Active(const std::string& name)
	{
		if (!s_Initialised)
		{
			Logger::Error("Cannot perform Renderer action [{0}]: Renderer not initialised!", name);
			return false;
		}

		return true;
	}

	void Renderer::Initialise()
	{
		if (s_Initialised)
		{
			// Whoops...
			Logger::Warn("Cannot initialise Renderer: Renderer was already initialised!");
			return;
		}

		// Initialise glad
		// A context MUST be set before this can return a successful result
		int gladStatus = gladLoadGL((GLADloadfunc)glfwGetProcAddress);
		_ASSERT(gladStatus);

		s_Initialised = true;

		// Dump info
		Logger::Trace("Renderer Initialised...");
		Logger::Info("OpenGL Info:\n\tVersion: {0}\n\tVendor: {1}\n\tDevice: {2}",
			glGetString(GL_VERSION), glGetString(GL_VENDOR), glGetString(GL_RENDERER));
	}
	
	void Renderer::Shutdown()
	{
		if (Active(__func__))
		{
			Logger::Trace("Renderer Shutdown...");
			s_Initialised = false;
		}
	}

	void Renderer::BeginFrame()
	{
		if (Active(__func__))
		{

		}
	}

	void Renderer::EndFrame()
	{
		if (Active(__func__))
		{

		}
	}
	
	void Renderer::Clear(float r, float g, float b, float a)
	{
		if (Active(__func__))
		{
			glClearColor(r, g, b, a);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
}