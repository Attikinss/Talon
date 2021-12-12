#pragma once
#include "Component.h"

#include <glm/glm.hpp>

namespace Talon
{
	class Transform : public Component
	{
		friend class Entity;

	public:
		Transform() = default;
		Transform(const glm::mat4& transform)
			: m_Transform(transform) { }

		void Set(const glm::mat4& transform) { m_Transform = transform; }

		static const char* GetName() { return "Transform"; }

	private:
		glm::mat4 m_Transform = glm::mat4(1.0f);
	};
}