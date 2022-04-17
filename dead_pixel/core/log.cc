#include "log.hh"

#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace DP {

std::shared_ptr<spdlog::logger> Logger::engine_logger;
std::shared_ptr<spdlog::logger> Logger::client_logger;

void Logger::init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	engine_logger = spdlog::stdout_color_mt("DeadPixel");
	engine_logger->set_level(spdlog::level::trace);

	client_logger = spdlog::stdout_color_mt("Application");
	client_logger->set_level(spdlog::level::trace);
}

}
