#include "EntityRegistry.h"
#include "Entity.h"

#include <glm/gtx/matrix_decompose.hpp>

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

	EntityRegistry::EntityRegistry()
	{
		
	}

	EntityRegistry::~EntityRegistry()
	{

	}

	void EntityRegistry::Update()
	{
		// Update all transforms in scene
		auto transformView = m_Registry.view<Transform>();
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
	}

	entt::entity EntityRegistry::CreateEntity()
	{
		return m_Registry.create();
	}

	void EntityRegistry::DestroyEntity(entt::entity entityHandle)
	{
		m_Registry.destroy(entityHandle);
	}
}