#pragma once
#include "Component.h"

#include <glm/glm.hpp>

namespace Talon
{
	class WorldCamera : public Component
	{
	public:
		WorldCamera() = default;
		virtual ~WorldCamera() = default;

		const glm::mat4& GetProjection() const { return m_ProjectionMatrix; }
		const char* GetName() override { return "Camera"; }

	protected:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
	};
}