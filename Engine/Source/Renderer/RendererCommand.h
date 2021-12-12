#pragma once

namespace Talon
{
	class Camera;

	class RendererCommand
	{
	public:
		static void BeginFrame(const Camera& camera);
		static void EndFrame();
		static void Clear(float r, float g, float b, float a = 1.0f);
	};
}