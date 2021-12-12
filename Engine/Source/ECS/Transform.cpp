#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Talon
{
	glm::quat GetOrientation(const glm::vec3& rotation)
	{
		return glm::quat(glm::radians(rotation * -1.0f));
	}

	void Transform::Set(const glm::mat4& transform)
	{
		m_Transform = transform;
	}

	void Transform::SetPosition(const glm::vec3& position)
	{
		m_Transform[3] = glm::vec4(position, 1.0f);
	}

	void Transform::SetRotation(const glm::vec3& rotation)
	{
		m_Transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_Transform[3])) * glm::toMat4(GetOrientation(rotation));
	}

	void Transform::Move(const glm::vec3& delta)
	{
		m_Transform = glm::translate(m_Transform, delta);
	}

	void Transform::Rotate(const glm::vec3& delta)
	{
		m_Transform *= glm::toMat4(GetOrientation(delta));
	}

	void Transform::Rotate(const glm::quat& delta)
	{
		m_Transform *= glm::toMat4(delta);
	}
}