#pragma once
#include "RendererCommand.h"

#include "glm/glm.hpp"
#include <memory>

namespace Talon
{
	class Camera;
	class MeshRenderer;

	class Renderer
	{
		friend class RendererCommand;

	public:
		static void Initialise();
		static void Shutdown();

	private:
		static void BeginFrame(const Camera& camera);
		static void EndFrame();
		static void Clear();
		static void Submit(const MeshRenderer& meshRenderer, const glm::mat4& transform);

		static void SetClearColour(const glm::vec4& colour);
		static void SetDepthTest(bool enabled);
		static void SetFaceCull(bool enabled);
		static void SetFaceCullType(FaceCullType type);
		static void SetPrimitiveType(PrimitiveType type);
	};
}