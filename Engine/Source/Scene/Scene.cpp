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
	}

	Scene::~Scene()
	{
		m_Selection.clear();
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
			transform.EulerAngles = glm::degrees(glm::eulerAngles(rotation));
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

			if (camera.Enabled)
			{
				glm::mat4 transform = camera.m_Entity->GetComponent<Transform>().GetTransform();
				camera.GetCamera().SetView(glm::inverse(transform));
			}
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

			if (meshRenderer.Enabled)
			{
				glm::mat4 transform = meshRenderer.m_Entity->GetComponent<Transform>().GetTransform();
				RendererCommand::Submit(meshRenderer, transform);
			}
		}

		// TODO: Add lighting handover

		RendererCommand::EndFrame();
	}

	void Scene::OnEvent(Event& evt)
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity(this, m_Registry.CreateEntity());
		entity.AddComponent<EntityInfo>(name);
		entity.AddComponent<Transform>();

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.DestroyEntity(entity.m_EntityHandle);
	}

	void Scene::AddToSelection(Entity selection)
	{
		// Only add entity if it's not already selected
		if (std::find(m_Selection.begin(), m_Selection.end(), selection) == m_Selection.end())
			m_Selection.push_back(selection);
	}
}