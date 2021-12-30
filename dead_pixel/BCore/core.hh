#pragma once

#ifdef DP_BUILD
// TODO: FIX THIS SO IT WORKS ON OTHER COMPILERS
#define DP_API __attribute__((visibility("default")))
#else
#define DP_API
#endif
