#pragma once

#include <signal.h>

#define ASSERT(condition) \
	if(!(condition)) raise(SIGABRT);
