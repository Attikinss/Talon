#pragma once
#include "glm/glm.hpp"
#include <memory>

namespace Talon
{
	class Camera;
	class Mesh;

	enum class PrimitiveType
	{
		Triangles = 0,
		Lines,
		Points,
	};

	enum class FaceCullType
	{
		None = 0,
		Front,
		Back,
		Both,
	};

	class RendererCommand
	{
	public:
		static void BeginFrame(const Camera& camera);
		static void EndFrame();
		static void Clear();
		static void Submit(const std::shared_ptr<Mesh>& mesh, const glm::mat4& transform);

		static void SetClearColour(const glm::vec4& colour);
		static void SetDepthTest(bool enabled);
		static void SetFaceCull(bool enabled);
		static void SetFaceCullType(FaceCullType type);
		static void SetPrimitiveType(PrimitiveType type);
	};
}