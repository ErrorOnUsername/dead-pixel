#pragma once

// FIXME: I don't know if this exists on all compilers! Verify!

using usize = __SIZE_TYPE__;

using u8  = __UINT8_TYPE__;
using u16 = __UINT16_TYPE__;
using u32 = __UINT32_TYPE__;
using u64 = __UINT64_TYPE__;

using i8  = __INT8_TYPE__;
using i16 = __INT16_TYPE__;
using i32 = __INT32_TYPE__;
using i64 = __INT64_TYPE__;

#define PACKED __attribute__((packed))
