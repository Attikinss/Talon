#include "Scene.h"

#include "ECS/Entity.h"
#include "ECS/MeshRenderer.h"
#include "ECS/Transform.h"
#include "ECS/WorldCamera.h"

#include "Renderer/RendererCommand.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Talon
{
	namespace Utilities
	{
		void DecomposeMatrix(const glm::mat4& matrix, glm::vec3& position, glm::quat& rotation, glm::vec3& scale)
		{
			position = matrix[3];

			scale[0] = glm::length(glm::vec3(matrix[0]));
			scale[1] = glm::length(glm::vec3(matrix[1]));
			scale[2] = glm::length(glm::vec3(matrix[2]));

			const glm::mat3 rotationMatrix(
				glm::vec3(matrix[0]) / scale[0],
				glm::vec3(matrix[1]) / scale[1],
				glm::vec3(matrix[2]) / scale[2]);

			rotation = glm::quat_cast(rotationMatrix);
		}
	}

	Scene::Scene(const std::string& name)
		: m_Name(name)
	{
		if (!s_CurrentScene)
		{
			s_CurrentScene = this;
			m_IsCurrent = true;
		}
	}

	Scene::~Scene()
	{

	}

	void Scene::Update()
	{
		// Update all transforms in the scene
		auto transformView = m_Registry.GetComponentsOfType<Transform>();
		for (auto entity : transformView)
		{
			// Get component from view
			Transform& transform = transformView.get<Transform>(entity);

			// Decompose transform
			glm::mat4 t = transform.UpdateTransform();
			glm::vec3 position;
			glm::quat rotation;
			glm::vec3 scale;
			Utilities::DecomposeMatrix(t, scale, rotation, position);

			// Update vectors
			transform.Up = glm::normalize(glm::rotate(rotation, glm::vec3(0.0f, 1.0f, 0.0f)));
			transform.Right = glm::normalize(glm::rotate(rotation, glm::vec3(1.0f, 0.0f, 0.0f)));
			transform.Forward = glm::normalize(glm::rotate(rotation, glm::vec3(0.0f, 0.0f, -1.0f)));
		}

		// Update all cameras in the scene
		// TODO: Only update if camera is the primary world camera
		auto cameraView = m_Registry.GetComponentsOfType<WorldCamera>();
		for (auto entity : cameraView)
		{
			// Get component from view
			WorldCamera& camera = cameraView.get<WorldCamera>(entity);
			glm::mat4 transform = camera.m_Entity->GetComponent<Transform>().GetTransform();

			camera.GetCamera().SetView(glm::inverse(transform));
		}
	}

	void Scene::Render(const Camera& camera)
	{
		RendererCommand::Clear();
		RendererCommand::BeginFrame(camera);
		
		// Update all meshes in the scene
		auto meshRendererView = m_Registry.GetComponentsOfType<MeshRenderer>();
		for (auto entity : meshRendererView)
		{
			// Get component from view
			MeshRenderer& meshRenderer = meshRendererView.get<MeshRenderer>(entity);
			glm::mat4 transform = meshRenderer.m_Entity->GetComponent<Transform>().GetTransform();

			RendererCommand::Submit(meshRenderer, transform);
		}

		RendererCommand::EndFrame();
	}

	void Scene::OnEvent(Event& evt)
	{

	}

	Entity Scene::CreateEntity()
	{
		Entity entity(this, m_Registry.CreateEntity());
		entity.AddComponent<Transform>();

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.DestroyEntity(entity.m_EntityHandle);
	}
}