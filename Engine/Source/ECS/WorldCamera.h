#pragma once
#include "Component.h"
#include "Renderer/Camera.h"

#include <glm/glm.hpp>

namespace Talon
{
	class WorldCamera : public Component
	{
		friend class Entity;

	public:
		WorldCamera() = default;
		~WorldCamera() = default;

		void SetPosition(const glm::vec3 position)
		{
			Transform& transform = m_Entity->GetComponent<Transform>();
			transform.SetPosition(position);

			m_Camera.SetView(glm::inverse(glm::mat4(transform)));
		}

		void SetRotation(const glm::vec3 rotation)
		{
			Transform& transform = m_Entity->GetComponent<Transform>();
			transform.SetRotation(rotation);

			m_Camera.SetView(glm::inverse(glm::mat4(transform)));
		}

		operator Camera&() { return m_Camera; }
		operator const Camera&() const { return m_Camera; }

		static const char* GetName() { return "Camera"; }

	private:
		Camera m_Camera;
	};
}