#include "Application.h"
#include "Defines.h"
#include "Logger.h"
#include "Events/ApplicationEvent.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Talon
{
	Application::Application()
	{
		Logger::Initialise();

		// Specify window creation details
		WindowCreateInfo winCreateInfo;
		winCreateInfo.Fullscreen = false;
		winCreateInfo.Width = 1280;
		winCreateInfo.Height = 720;
		winCreateInfo.Title = "Talon";
		winCreateInfo.VSync = true;

		m_Window = Window::Create(winCreateInfo);
		m_Window->SetEventCallback(BIND_FUNCTION(Application::ProcessEvents));

		Renderer::Initialise();

		m_LayerStack = new LayerStack();

		m_Running = true;
	}

	Application::~Application()
	{
		Renderer::Shutdown();

		delete m_LayerStack;
		delete m_Window;
	}

	void Application::Run()
	{
		auto shader = Shader::Create("Assets/Shaders/Basic.glsl");
		shader->Bind();

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
		};

		uint32_t vao, vbo;
		
		// Create and bind vertex buffer
		glCreateBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// Write vertex data to buffer
		glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Create and bind vertex array
		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Enable and setup attrib pointer data
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)(sizeof(float) * 0));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)(sizeof(float) * 1));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)(sizeof(float) * 2));

		for (Layer* layer : *m_LayerStack)
			layer->Initialise();

		while (m_Running)
		{
			m_Window->GetContext().ProcessEvents();

			RendererCommand::Clear(0.15f, 0.15f, 0.15f);
			RendererCommand::BeginFrame();

			// Update all layers
			for (Layer* layer : *m_LayerStack)
				layer->Update();

			glDrawArrays(GL_TRIANGLES, 0, 3);

			RendererCommand::EndFrame();

			m_Window->GetContext().SwapBuffers();
		}

		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);

		delete shader;
	}

	void Application::ProcessEvents(Event& evt)
	{
		EventDispatcher dispatcher(evt);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FUNCTION(Application::OnWindowClose));

		// Iterate back to front passing the event to each layer
		for (auto it = m_LayerStack->rend(); it != m_LayerStack->rbegin();)
		{
			// Bail once the event has been handled
			if (evt.m_Used)
				break;

			// Process the event on the current layer
			(*--it)->ProcessEvents(evt);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack->PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack->PushOverlay(layer);
	}

	Window& Application::GetWindow() const
	{
		return *m_Window;
	}

	bool Application::OnWindowClose(WindowCloseEvent& evt)
	{
		m_Running = false;
		return false;
	}
}