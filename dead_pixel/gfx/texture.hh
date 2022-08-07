#pragma once

#include <core/types.hh>
#include <core/memory.hh>

namespace DP {

struct Texture {
	u32         id;
	bool        is_loaded;
	char const* path;

	u32 width;
	u32 height;
	u32 internal_format;
	u32 data_format;

	static RefPtr<Texture> create(u32 width, u32 height)
	{
		return make_ref_ptr<Texture>(width, height);
	}

	static RefPtr<Texture> create(char const* path)
	{
		return make_ref_ptr<Texture>(path);
	}

	Texture(u32 width, u32 height);
	Texture(char const* path);

	~Texture();

	void set_data(void* data, u32 size);

	void bind(u32 slot = 0);
	void unbind();
};

}
