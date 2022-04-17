#pragma once
#include <signal.h>

#include <core/log.hh>

#define _STRINGIFY_HELPER(x) #x
#define _STRINGIFY(x) _STRINGIFY_HELPER(x)

#define __HANDLE_ASSERT_FAILED_WITH_MESSAGE_FORMAT__(condition, msg, fmt...)                   \
	DP_ENGINE_CRITICAL("[" __FILE__ ":" _STRINGIFY(__LINE__) "] Assertion Failed: " msg, fmt); \
	raise(SIGABRT);

#define __HANDLE_ASSERT_FAILED_WITH_MESSAGE__(condition, msg)                      \
	DP_ENGINE_CRITICAL("[" __FILE__ ":" _STRINGIFY(__LINE__) "] Assertion Failed: " msg); \
	raise(SIGABRT);

#define ASSERT_FMT(condition, msg, ...) do { if(!(condition)) { __HANDLE_ASSERT_FAILED_WITH_MESSAGE_FORMAT__(condition, msg, __VA_ARGS__) } } while(0)
#define ASSERT(condition, msg) do { if(!(condition)) { __HANDLE_ASSERT_FAILED_WITH_MESSAGE__(condition, msg) } } while(0)
