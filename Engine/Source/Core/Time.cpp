#include "Time.h"
#include "Logger.h"

namespace Talon
{
	static float s_CurrentTime = 0.0f;
	static float s_DeltaTime = 0.0f;
	static const float s_FixedDeltaTime = 0.0f;
	static float s_PreviousTime = 0.0f;

	static std::chrono::time_point<std::chrono::high_resolution_clock> s_Start;

	static float ElapsedTime()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - s_Start).count() * 0.001f * 0.001f * 0.001f;
	}

	void Time::Initialise()
	{
		s_Start = std::chrono::high_resolution_clock::now();
		Logger::Trace("Time Initialised...");
	}

	void Time::Update()
	{
		s_CurrentTime = ElapsedTime();
		s_DeltaTime = s_CurrentTime - s_PreviousTime;
		s_PreviousTime = s_CurrentTime;
	}

	float Time::CurrentTime()
	{
		return s_CurrentTime;
	}

	float Time::DeltaTime()
	{
		return s_DeltaTime;
	}

	float Time::FixedDeltaTime()
	{
		return s_FixedDeltaTime;
	}
}