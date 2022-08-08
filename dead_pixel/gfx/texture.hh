#pragma once

#include <core/types.hh>

namespace DP {

struct Texture {
	u32         id;
	bool        is_loaded;
	char const* path;

	u32 width;
	u32 height;
	u32 internal_format;
	u32 data_format;

	Texture(u32 width, u32 height);
	Texture(char const* path);

	~Texture();

	void set_data(void* data, u32 size);

	void bind(u32 slot = 0);
	void unbind();
};

}
