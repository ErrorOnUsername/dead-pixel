#pragma once
#include <vector>

#include <core/types.hh>

namespace DP {

enum class FramebufferTextureFormat : u32 {
	None = 0,
	RGBA8,
	RedInteger,
	Depth24Stencil8,
	Depth = Depth24Stencil8,
};

struct FramebufferFormat {
	u32 width   = 0;
	u32 height  = 0;
	u32 samples = 1;
	std::vector<FramebufferTextureFormat> attachments;
};

struct Framebuffer {
	FramebufferFormat format;
	u32               framebuffer_id;

	std::vector<FramebufferTextureFormat> color_format_attachments;
	std::vector<uint32_t>                 framebuffer_color_texture_ids;
	FramebufferTextureFormat              depth_attachment;
	uint32_t                              framebuffer_depth_texture_id;

	Framebuffer(FramebufferFormat fmt);
	~Framebuffer();

	void bind();
	void unbind();

	void resize(u32 new_width, u32 new_height);

	void invalidate();
	int  read_pixel(u32 attachment_index, int x, int y);

	u32  attachment_id(u32 index = 0);
	void clear_attachment(u32 attachment, int value);
};

}
