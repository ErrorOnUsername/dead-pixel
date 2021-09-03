#include "Log.h"
#include <vector>

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#pragma warning(pop)

namespace DP {
shared_ptr<spdlog::logger> Log::s_engine_logger;
shared_ptr<spdlog::logger> Log::s_client_logger;

void Log::init()
{
	std::vector<spdlog::sink_ptr> sinks;
	sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("DeadPixel.log", true));

	sinks[0]->set_pattern("%^[%n | %T] : %v%$");
	sinks[1]->set_pattern("[%n | %T] [%l] : %v");

	s_engine_logger = std::make_shared<spdlog::logger>("ENGINE", std::begin(sinks), std::end(sinks));
	spdlog::register_logger(s_engine_logger);
	s_engine_logger->set_level(spdlog::level::trace);
	s_engine_logger->flush_on(spdlog::level::trace);

	s_client_logger = std::make_shared<spdlog::logger>("EDITOR", std::begin(sinks), std::end(sinks));
	spdlog::register_logger(s_client_logger);
	s_client_logger->set_level(spdlog::level::trace);
	s_client_logger->flush_on(spdlog::level::trace);
}
}
