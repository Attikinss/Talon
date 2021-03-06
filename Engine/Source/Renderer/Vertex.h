#pragma once
#include <glm/glm.hpp>

namespace Talon
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 UV;
		glm::vec3 Tangent;
		glm::vec3 BiTangent;
	};
}