#include "RendererCommand.h"

#include "Renderer.h"

namespace Talon
{
	void RendererCommand::BeginFrame()
	{
		Renderer::BeginFrame();
	}

	void RendererCommand::EndFrame()
	{
		Renderer::EndFrame();
	}

	void RendererCommand::Clear(float r, float g, float b, float a)
	{
		Renderer::Clear(r, g, b, a);
	}
}