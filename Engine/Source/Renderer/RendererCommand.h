#pragma once
#include "glm/glm.hpp"

namespace Talon
{
	class Camera;
	class Mesh;

	class RendererCommand
	{
	public:
		static void BeginFrame(const Camera& camera);
		static void EndFrame();
		static void Clear(float r, float g, float b, float a = 1.0f);
		static void Submit(Mesh* mesh, const glm::mat4& transform);
	};
}