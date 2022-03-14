#pragma once

#include <core/memory.hh>

namespace DP {

struct Texture {
	uint32_t id;

	Texture(char const* filepath);
	~Texture();

	static RefPtr<Texture> create();
};

}
