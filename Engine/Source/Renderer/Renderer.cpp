#include "Renderer.h"

#include "Core/Logger.h"
#include "Camera.h"
#include "Shader.h"
#include "VertexArray.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Talon
{
	struct RendererData
	{
		Shader* TestShader = nullptr;
		VertexArray* VAO = nullptr;
		glm::mat4 ViewProjMatrix = glm::mat4(1.0f);

		RendererData()
		{
			TestShader = new Shader("Assets/Shaders/Basic.glsl");

			float vertices[] =
			{
				// Positions			UVs
				-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
				-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,
				 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
			};

			uint32_t indices[] =
			{
				0, 1, 2, 3, 2, 0
			};

			auto indexBuffer = IndexBuffer::Create(sizeof(indices), indices);
			auto vertexBuffer = VertexBuffer::Create(sizeof(vertices), vertices);
			vertexBuffer->SetLayout({
				{ DataType::Float3, "a_Position" },
				{ DataType::Float2, "a_UVs" },
			});

			VAO = new VertexArray();
			VAO->AddVertexBuffer(vertexBuffer);
			VAO->SetIndexBuffer(indexBuffer);
			
			// These are only here temporarily to draw the square until
			// a more permanent solution for model submission is created
			TestShader->Bind();
			VAO->Bind();
			VAO->GetIndexBuffer()->Bind();
		}

		~RendererData()
		{
			delete TestShader;
			delete VAO;
		}
	};

	static RendererData* s_RendererData = nullptr;
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

		s_RendererData = new RendererData();

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
			delete s_RendererData;

			Logger::Trace("Renderer Shutdown...");
			s_Initialised = false;
		}
	}

	void Renderer::BeginFrame(const Camera& camera)
	{
		if (Active(__func__))
		{
			s_RendererData->ViewProjMatrix = camera.GetViewProjection();
			s_RendererData->TestShader->SetUniform("u_ModelMatrix", glm::mat4(1.0f));
			s_RendererData->TestShader->SetUniform("u_ViewProjectionMatrix", s_RendererData->ViewProjMatrix);
		}
	}

	void Renderer::EndFrame()
	{
		if (Active(__func__))
		{
			glDrawElements(GL_TRIANGLES, s_RendererData->VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
		}
	}
	
	void Renderer::Clear(float r, float g, float b, float a)
	{
		if (Active(__func__))
		{
			// TODO: Move into GLState class or something

			glClearColor(r, g, b, a);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
}