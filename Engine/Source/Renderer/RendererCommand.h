#pragma once

namespace Talon
{
	class RendererCommand
	{
	public:
		static void BeginFrame();
		static void EndFrame();
		static void Clear(float r, float g, float b, float a = 1.0f);
	};
}