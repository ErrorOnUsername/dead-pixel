#include "log.hh"

#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace DP {

std::shared_ptr<spdlog::logger> Logger::s_engine_logger;
std::shared_ptr<spdlog::logger> Logger::s_client_logger;

void Logger::init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_engine_logger = spdlog::stdout_color_mt("DeadPixel");
	s_engine_logger->set_level(spdlog::level::trace);

	s_client_logger = spdlog::stdout_color_mt("Application");
	s_client_logger->set_level(spdlog::level::trace);
}

}
