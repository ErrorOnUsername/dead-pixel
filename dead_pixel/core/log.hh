#pragma once
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <core/core.hh>

namespace DP {

class DP_API Logger {
public:
	static void init();

	inline static std::shared_ptr<spdlog::logger> engine_logger() { return s_engine_logger; }
	inline static std::shared_ptr<spdlog::logger> client_logger() { return s_client_logger; }
private:
	static std::shared_ptr<spdlog::logger> s_engine_logger;
	static std::shared_ptr<spdlog::logger> s_client_logger;
};

}

#define DP_ENGINE_CRITICAL(...) ::DP::Logger::engine_logger()->critical(__VA_ARGS__)
#define DP_ENGINE_ERROR(...)    ::DP::Logger::engine_logger()->error(__VA_ARGS__)
#define DP_ENGINE_WARN(...)     ::DP::Logger::engine_logger()->warn(__VA_ARGS__)
#define DP_ENGINE_INFO(...)     ::DP::Logger::engine_logger()->info(__VA_ARGS__)
#define DP_ENGINE_TRACE(...)    ::DP::Logger::engine_logger()->trace(__VA_ARGS__)

#define DP_CRITICAL(...) ::DP::Logger::client_logger()->critical(__VA_ARGS__)
#define DP_ERROR(...)    ::DP::Logger::client_logger()->error(__VA_ARGS__)
#define DP_WARN(...)     ::DP::Logger::client_logger()->warn(__VA_ARGS__)
#define DP_INFO(...)     ::DP::Logger::client_logger()->info(__VA_ARGS__)
#define DP_TRACE(...)    ::DP::Logger::engine_logger()->trace(__VA_ARGS__)
