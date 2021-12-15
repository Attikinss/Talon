#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Talon
{
	void Transform::OnUpdate()
	{
		m_Transform = glm::translate(glm::mat4(1.0f), Position) * glm::toMat4(Rotation) * glm::scale(glm::mat4(1.0f), Scale);
	}

	void Transform::OnEditorUpdate()
	{
		Rotation = glm::quat(EulerAngles);
		OnUpdate();
	}
}