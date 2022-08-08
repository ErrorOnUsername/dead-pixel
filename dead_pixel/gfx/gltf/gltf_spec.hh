#pragma once
#include <core/types.hh>

constexpr u32 GLB_MAGIC = 0x46546C67; // "glTF" in ASCII

constexpr u32 GLB_CHUNK_TYPE_JSON   = 0x4E4F534A; // "JSON" in ASCII
constexpr u32 GLB_CHUNK_TYPE_BINARY = 0x004E4942;   // "BIN" in ASCII

struct GLBHeader {
	u32 magic;
	u32 version;
	u32 length;
} PACKED;
static_assert(sizeof(GLBHeader) == 12);

struct GLBChunk {
	u32 chunk_length;
	u32 chunk_type;
	u8* chunk_data;
} PACKED;
static_assert(sizeof(GLBChunk) == 16);
