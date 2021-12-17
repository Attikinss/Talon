#include "RendererCommand.h"

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

	void RendererCommand::Clear(float r, float g, float b, float a)
	{
		Renderer::Clear(r, g, b, a);
	}

	void RendererCommand::Submit(const std::shared_ptr<Mesh>& mesh, const glm::mat4& transform)
	{
		Renderer::Submit(mesh, transform);
	}
}