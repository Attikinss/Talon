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
		Transform(const glm::mat4& transform)
			: m_Transform(transform) { }

		void Set(const glm::mat4& transform);

		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);

		void Move(const glm::vec3& delta);
		void Rotate(const glm::vec3& delta);
		void Rotate(const glm::quat& delta);

		operator const glm::mat4&() const { return m_Transform; }

		static const char* GetName() { return "Transform"; }

	private:
		glm::mat4 m_Transform = glm::mat4(1.0f);
	};
}