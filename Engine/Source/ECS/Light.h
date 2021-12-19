#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace Talon
{
	class Light : public Component
	{
	public:
		enum class Type { Directional, Point, Spot };

	public:
		Light() = default;
		Light(Type type)
			: Type(type) { }
		~Light() = default;

		static const char* GetName() { return "Light"; }

	public:
		Type Type = Type::Directional;
		glm::vec4 Colour = { 1.0f, 0.96f, 0.85f, 1.0f };
		float Intensity = 1.0f;
	};
}