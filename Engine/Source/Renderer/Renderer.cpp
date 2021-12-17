#include "Renderer.h"

#include "Core/Logger.h"
#include "Camera.h"
#include "MeshLoader.h"
#include "Shader.h"
#include "Texture.h"
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
		Texture2D* TestTexture = nullptr;
		VertexArray* VAO = nullptr;

		glm::mat4 ViewProjMatrix = glm::mat4(1.0f);

		RendererData()
		{
			TestShader = new Shader("Assets/Shaders/Basic.glsl");
			TestTexture = new Texture2D("Assets/Textures/whenquadisblack.jpg");

			auto indexBuffer = IndexBuffer::Create(1000 * sizeof(uint32_t));
			auto vertexBuffer = VertexBuffer::Create(20000 * sizeof(Vertex));
			
			vertexBuffer->SetLayout({
				{ DataType::Float3, "a_Position" },
				{ DataType::Float3, "a_Normals" },
				{ DataType::Float2, "a_UVs" },
				{ DataType::Float3, "a_Tangent" },
				{ DataType::Float3, "a_BiTangent" },
			});

			VAO = new VertexArray();
			VAO->AddVertexBuffer(vertexBuffer);
			VAO->SetIndexBuffer(indexBuffer);
		}

		~RendererData()
		{
			delete TestShader;
			delete TestTexture;
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

		// Enable depth testing
		glEnable(GL_DEPTH_TEST);

		// Enable face culling
		glEnable(GL_CULL_FACE);

		// Set back face culling mode
		glCullFace(GL_BACK);

		// Enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
			// These are only here temporarily to draw the quad until
			// a more permanent solution for model submission is created
			s_RendererData->TestShader->Bind();
			s_RendererData->TestTexture->Bind();
			s_RendererData->VAO->Bind();
			s_RendererData->VAO->GetIndexBuffer()->Bind();

			s_RendererData->ViewProjMatrix = camera.GetViewProjection();
			s_RendererData->TestShader->SetUniform("u_TestTexture", 0);
			s_RendererData->TestShader->SetUniform("u_ViewProjectionMatrix", s_RendererData->ViewProjMatrix);
		}
	}

	void Renderer::EndFrame()
	{
		if (Active(__func__))
		{
			//glDrawElements(GL_TRIANGLES, s_RendererData->VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
		}
	}
	
	void Renderer::Clear(float r, float g, float b, float a)
	{
		if (Active(__func__))
		{
			// TODO: Move into GLState class or something

			glClearColor(r, g, b, a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}

	void Renderer::Submit(Mesh* mesh, const glm::mat4& transform)
	{
		// TODO: Draw objects at EndFrame rather than immediately

		s_RendererData->TestShader->SetUniform("u_ModelMatrix", transform);
		s_RendererData->VAO->GetVertexBuffers()[0]->SetData((uint32_t)mesh->GetVertices().size() * sizeof(Vertex), (void*)mesh->GetVertices().data());
		s_RendererData->VAO->GetIndexBuffer()->SetData((uint32_t)mesh->GetIndices().size() * sizeof(uint32_t), (void*)mesh->GetIndices().data());

		glDrawElements(GL_TRIANGLES, s_RendererData->VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	}
}