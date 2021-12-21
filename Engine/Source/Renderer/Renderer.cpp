#include "Renderer.h"

#include "Core/Logger.h"
#include "Camera.h"
#include "MeshLoader.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "UniformBuffer.h"
#include "VertexArray.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Talon
{
	struct CameraData
	{
		glm::mat4 ViewProjMatrix = glm::mat4(1.0f);
		glm::vec3 ViewPosition = glm::vec3(0.0f);
	};

	struct RendererData
	{
		Shader* MissingMatShader = nullptr;
		VertexArray* VAO = nullptr;
		UniformBuffer* UBO = nullptr;

		GLenum PrimitiveType = GL_TRIANGLES;
		uint32_t ClearFlags = 0;

		CameraData CameraBuffer;

		RendererData()
		{
			MissingMatShader = new Shader("Assets/Shaders/MissingMat.glsl");

			auto indexBuffer = IndexBuffer::Create(12500 * sizeof(uint32_t));
			auto vertexBuffer = VertexBuffer::Create(7500 * sizeof(Vertex));
			
			vertexBuffer->SetLayout({
				{ DataType::Float3, "a_Position" },
				{ DataType::Float3, "a_Normal" },
				{ DataType::Float2, "a_UV" },
				{ DataType::Float3, "a_Tangent" },
				{ DataType::Float3, "a_BiTangent" },
			});

			VAO = new VertexArray();
			VAO->AddVertexBuffer(vertexBuffer);
			VAO->SetIndexBuffer(indexBuffer);

			UBO = new UniformBuffer((uint32_t)sizeof(CameraData), 0);
		}

		~RendererData()
		{
			delete MissingMatShader;
			delete VAO;
			delete UBO;
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
			s_RendererData->CameraBuffer.ViewProjMatrix = camera.GetViewProjection();
			s_RendererData->CameraBuffer.ViewPosition = glm::inverse(camera.GetView())[3];

			// These are only here temporarily to draw the quad until
			// a more permanent solution for model submission is created
			s_RendererData->VAO->Bind();
			s_RendererData->VAO->GetIndexBuffer()->Bind();

			s_RendererData->UBO->SetData((uint32_t)sizeof(CameraData), &s_RendererData->CameraBuffer, 0);
		}
	}

	void Renderer::EndFrame()
	{
		if (Active(__func__))
		{
			//glDrawElements(GL_TRIANGLES, s_RendererData->VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
		}
	}
	
	void Renderer::Clear()
	{
		if (Active(__func__))
		{
			glClear(GL_COLOR_BUFFER_BIT | s_RendererData->ClearFlags);
		}
	}

	void Renderer::Submit(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const glm::mat4& transform)
	{
		if (Active(__func__))
		{
			// TODO: Draw objects at EndFrame rather than immediately

			// Bail if there's no mesh to render
			if (!mesh.get())
				return;

			if (material.get())
			{
				material->Bind();
				material->SetMatrix4("u_ModelMatrix", transform);
				material->SetMatrix3("u_NormalMatrix", glm::mat3(glm::transpose(glm::inverse(transform))));
			}
			else
			{
				s_RendererData->MissingMatShader->Bind();
				s_RendererData->MissingMatShader->SetUniform("u_ModelMatrix", transform);
			}

			s_RendererData->VAO->GetVertexBuffers()[0]->SetData((uint32_t)mesh->GetVertices().size() * sizeof(Vertex), (void*)mesh->GetVertices().data());
			s_RendererData->VAO->GetIndexBuffer()->SetData((uint32_t)mesh->GetIndices().size() * sizeof(uint32_t), (void*)mesh->GetIndices().data());

			glDrawElements(s_RendererData->PrimitiveType, s_RendererData->VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
		}
	}

	void Renderer::SetClearColour(const glm::vec4& colour)
	{
		if (Active(__func__))
			glClearColor(colour.r, colour.g, colour.b, colour.a);
	}

	void Renderer::SetDepthTest(bool enabled)
	{
		if (Active(__func__))
		{
			if (enabled && !(s_RendererData->ClearFlags & GL_DEPTH_BUFFER_BIT))
				s_RendererData->ClearFlags |= GL_DEPTH_BUFFER_BIT;

			else if (!enabled && s_RendererData->ClearFlags & GL_DEPTH_BUFFER_BIT)
				s_RendererData->ClearFlags = s_RendererData->ClearFlags & ~GL_DEPTH_BUFFER_BIT;
		}
	}

	void Renderer::SetFaceCull(bool enabled)
	{
		if (Active(__func__))
		{
			if (enabled)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);
		}
	}

	void Renderer::SetFaceCullType(FaceCullType type)
	{
		if (Active(__func__))
		{
			switch (type)
			{
			case Talon::FaceCullType::None:
				glCullFace(GL_NONE);
				break;

			case Talon::FaceCullType::Front:
				glCullFace(GL_FRONT);
				break;

			case Talon::FaceCullType::Back:
				glCullFace(GL_BACK);
				break;

			case Talon::FaceCullType::Both:
				glCullFace(GL_FRONT_AND_BACK);
				break;

			default:
				Logger::Warn("({0}) - Invalid value selected!", __func__);
				break;
			}
		}
	}

	void Renderer::SetPrimitiveType(PrimitiveType type)
	{
		if (Active(__func__))
		{
			switch (type)
			{
			case Talon::PrimitiveType::Triangles:
				s_RendererData->PrimitiveType = GL_TRIANGLES;
				break;

			case Talon::PrimitiveType::Lines:
				s_RendererData->PrimitiveType = GL_LINES;
				break;

			case Talon::PrimitiveType::Points:
				s_RendererData->PrimitiveType = GL_POINTS;
				break;

			default:
				Logger::Warn("({0}) - Invalid value selected!", __func__);
				break;
			}
		}
	}
}