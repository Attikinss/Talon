#pragma once
#include "Component.h"
#include "Renderer/Camera.h"

#include <glm/glm.hpp>

namespace Talon
{
	class WorldCamera : public Component
	{
		friend class Scene;

	public:
		WorldCamera() = default;
		~WorldCamera() = default;

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		static const char* GetName() { return "Camera"; }

	private:
		Camera m_Camera;
	};
}