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

		void OnEditorUpdate() override
		{
			OnUpdate();
		}

		void OnUpdate() override
		{
			Transform& transform = m_Entity->GetComponent<Transform>();
			m_Camera.SetView(glm::inverse(transform.GetTransform()));
		}

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		static const char* GetName() { return "Camera"; }

	private:
		Camera m_Camera;
	};
}