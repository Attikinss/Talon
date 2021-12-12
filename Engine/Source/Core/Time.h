#pragma once
#include <chrono>

namespace Talon
{
	class Time
	{
	public:
		static void Initialise();
		static void Update();

		static float CurrentTime();
		static float DeltaTime();
		static float FixedDeltaTime();
	};
}