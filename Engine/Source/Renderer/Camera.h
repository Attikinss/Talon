#pragma once
#include <glm/glm.hpp>

namespace Talon
{
	class Camera
	{
	public:
		Camera() = default;
		virtual ~Camera() = default;

		const glm::mat4& GetProjection() const { return m_ProjectionMatrix; }

	protected:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
	};
}