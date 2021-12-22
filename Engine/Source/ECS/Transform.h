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

		const glm::mat4& GetTransform() const { return m_Transform; }
		const glm::mat4 UpdateTransform() const { return glm::translate(glm::mat4(1.0f), Position) * glm::toMat4(glm::quat(Rotation)) * glm::scale(glm::mat4(1.0f), Scale); }
		static const char* GetName() { return "Transform"; }

	public:
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 EulerAngles = { 0.0f, 0.0f, 0.0f };
		glm::quat Rotation = { 0.0f, 0.0f, 0.0f, 1.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		glm::vec3 Up = { 0.0f, 1.0f, 0.0f };
		glm::vec3 Right = { 1.0f, 0.0f, 0.0f };
		glm::vec3 Forward = { 0.0f, 0.0f, -1.0f };

	private:
		glm::mat4 m_Transform = glm::mat4(1.0f);
	};
}