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
		WorldCamera() : m_Camera(new Camera()) { }

		~WorldCamera()
		{
			delete m_Camera;
		}

		static const char* GetName() { return "Camera"; }

	private:
		Camera* m_Camera = nullptr;
	};
}