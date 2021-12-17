#pragma once
#include "glm/glm.hpp"
#include <memory>

namespace Talon
{
	class Camera;
	class Mesh;

	class Renderer
	{
		friend class RendererCommand;

	public:
		static void Initialise();
		static void Shutdown();

	private:
		static void BeginFrame(const Camera& camera);
		static void EndFrame();

		// Move clear colour info into a GLState structure or something
		static void Clear(float r, float g, float b, float a);

		static void Submit(const std::shared_ptr<Mesh>& mesh, const glm::mat4& transform);
	};
}