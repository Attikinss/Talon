#pragma once

namespace Talon
{
	class Renderer
	{
		friend class RendererCommand;

	public:
		static void Initialise();
		static void Shutdown();

	private:
		static void BeginFrame();
		static void EndFrame();

		// Move clear colour info into a GLState structure or something
		static void Clear(float r, float g, float b, float a);
	};

	class RendererCommand
	{
	public:
		static void BeginFrame() { Renderer::BeginFrame(); }
		static void EndFrame() { Renderer::EndFrame(); }
		static void Clear(float r, float g, float b, float a = 1.0f) { Renderer::Clear(r, g, b, a); }
	};
}