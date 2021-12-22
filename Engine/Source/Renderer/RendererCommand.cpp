#include "RendererCommand.h"

#include "ECS/MeshRenderer.h"
#include "Renderer.h"

namespace Talon
{
	void RendererCommand::BeginFrame(const Camera& camera)
	{
		Renderer::BeginFrame(camera);
	}

	void RendererCommand::EndFrame()
	{
		Renderer::EndFrame();
	}

	void RendererCommand::Clear()
	{
		Renderer::Clear();
	}

	void RendererCommand::Submit(const MeshRenderer& meshRenderer, const glm::mat4& transform)
	{
		Renderer::Submit(meshRenderer, transform);
	}

	void RendererCommand::SetClearColour(const glm::vec4& colour)
	{
		Renderer::SetClearColour(colour);
	}

	void RendererCommand::SetDepthTest(bool enabled)
	{
		Renderer::SetDepthTest(enabled);
	}

	void RendererCommand::SetFaceCull(bool enabled)
	{
		Renderer::SetFaceCull(enabled);
	}

	void RendererCommand::SetFaceCullType(FaceCullType type)
	{
		Renderer::SetFaceCullType(type);
	}

	void RendererCommand::SetPrimitiveType(PrimitiveType type)
	{
		Renderer::SetPrimitiveType(type);
	}
}