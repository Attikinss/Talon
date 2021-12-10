#pragma once
#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.inl>
#include <glm/gtc/quaternion.hpp>

namespace Talon
{
	class Transform : public Component
	{
	public:
		Transform() = default;
		Transform(const Transform&) = default;
		Transform(const glm::mat4& transform)
		{
			SetTransform(transform);
		}

		void SetTransform(const glm::mat4& transform)
		{
			m_Transform = transform;
			Decompose(transform, m_Scale, m_Rotation, m_Position);
			m_Rotation = glm::conjugate(m_Rotation);
		}

		const char* GetName() override { return "Transform"; }

	private:
		void Decompose(const glm::mat4& matrix, glm::vec3& position, glm::quat& rotation, glm::vec3& scale)
		{
			position = matrix[3];

			scale[0] = glm::length(glm::vec3(matrix[0]));
			scale[1] = glm::length(glm::vec3(matrix[1]));
			scale[2] = glm::length(glm::vec3(matrix[2]));

			const glm::mat3 rotationMat(glm::vec3(matrix[0]) / scale[0],
										glm::vec3(matrix[1]) / scale[1],
										glm::vec3(matrix[2]) / scale[2]);

			// TODO: Use glm::conjugate afterwards to
			//		 invert rotation if it is flipped
			rotation = glm::quat_cast(rotationMat);
		}

	private:
		glm::mat4 m_Transform;
		glm::vec3 m_Position;
		glm::quat m_Rotation;
		glm::vec3 m_Scale;
	};
}