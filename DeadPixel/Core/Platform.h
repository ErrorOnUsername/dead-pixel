#pragma once

#ifdef _WIN32
	#ifdef _WIN64
		#define DP_PLATFORM_WINDOWS
		#error "Windows is not yet supported!"
	#else
		#error "32-bit Windows is not suppoerted!"
	#endif
#elif defined(__ANDROID__)
	#define DP_PLATFORM_ANDROID
	#error "Android is not yet supported"
#elif defined(__linux__)
	#define DP_PLATFORM_LINUX
	#error "Linux is not yet supported!"
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>

	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define DP_PLATFORM_IOS
		#error "IOS is not yet supported!"
	#elif TARGET_OS_MAC
		#define DP_PLATFORM_MACOS
	#elif
		#error "Unknown Apple platform!"
	#endif
#else
	#error "Unknown platform!"
#endif
