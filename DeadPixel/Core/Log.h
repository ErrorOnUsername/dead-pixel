#pragma once

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#pragma warning(pop)

#include <Core/Pointer.h>

namespace DP {
class Log {
public:
	static void init();

	static shared_ptr<spdlog::logger>& engine_logger() { return s_engine_logger; }
	static shared_ptr<spdlog::logger>& client_logger() { return s_client_logger; }

private:
	static shared_ptr<spdlog::logger> s_engine_logger;
	static shared_ptr<spdlog::logger> s_client_logger;
};
}

#define DP_ENGINE_TRACE(...)    ::DP::Log::engine_logger()->trace(__VA_ARGS__)
#define DP_ENGINE_INFO(...)     ::DP::Log::engine_logger()->info(__VA_ARGS__)
#define DP_ENGINE_WARN(...)     ::DP::Log::engine_logger()->warn(__VA_ARGS__)
#define DP_ENGINE_ERROR(...)    ::DP::Log::engine_logger()->error(__VA_ARGS__)
#define DP_ENGINE_CRITICAL(...) ::DP::Log::engine_logger()->critical(__VA_ARGS__)

#define DP_TRACE(...)           ::DP::Log::client_logger()->trace(__VA_ARGS__)
#define DP_INFO(...)            ::DP::Log::client_logger()->info(__VA_ARGS__)
#define DP_WARN(...)            ::DP::Log::client_logger()->warn(__VA_ARGS__)
#define DP_ERROR(...)           ::DP::Log::client_logger()->error(__VA_ARGS__)
#define DP_CRITICAL(...)        ::DP::Log::client_logger()->critical(__VA_ARGS__)