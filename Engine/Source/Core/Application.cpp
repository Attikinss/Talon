#include "Application.h"
#include "Defines.h"
#include "Logger.h"
#include "Events/ApplicationEvent.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

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
		shader->SetUniform("Colour", { 0.3, 0.8, 0.2f, 1.0f });

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
		};

		auto vertexBuffer = VertexBuffer::Create(sizeof(vertices), vertices);
		vertexBuffer->SetLayout({
			{ DataType::Float3, "a_Position" },
		});
		auto vertexArray = VertexArray::Create();
		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->Bind();

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