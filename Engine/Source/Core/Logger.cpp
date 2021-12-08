#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Talon
{
	std::shared_ptr<spdlog::logger> Logger::s_Logger = nullptr;

	void Logger::Initialise()
	{
		// Set formatting for log messages
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// Set name of engine logger and set it to print all messages to console
		s_Logger = spdlog::stdout_color_mt("TALON");
		s_Logger->set_level(spdlog::level::trace);

		Trace("Logger Initialised...");
	}
}