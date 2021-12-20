#pragma once
#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Talon
{
	class Transform : public Component
	{
		friend class Entity;

	public:
		Transform() = default;
		Transform(const glm::vec3& origin)
			: Position(origin) { }

		void OnEditorUpdate() override;
		void OnUpdate() override;

		const glm::mat4& GetTransform() const { return m_Transform; }
		static const char* GetName() { return "Transform"; }

		glm::vec3 GetForward() { return glm::normalize(m_Transform[2]); }

	public:
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 EulerAngles = { 0.0f, 0.0f, 0.0f };
		glm::quat Rotation = { 0.0f, 0.0f, 0.0f, 1.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

	private:
		glm::mat4 m_Transform = glm::mat4(1.0f);
	};
}