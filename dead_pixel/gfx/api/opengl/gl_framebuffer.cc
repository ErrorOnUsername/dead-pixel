#include <gfx/framebuffer.hh>

#include <glad/glad.h>

#include <core/assert.hh>
#include <core/log.hh>

namespace DP {

static inline GLuint texture_type(bool multisample)
{
	return (multisample) ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}

static GLenum to_gl_fbuff_type(FramebufferTextureFormat fmt)
{
	switch(fmt) {
		case FramebufferTextureFormat::RGBA8: return GL_RGBA8;
		case FramebufferTextureFormat::RedInteger: return GL_RED_INTEGER;
		case FramebufferTextureFormat::Depth24Stencil8: return GL_DEPTH24_STENCIL8;
		default:
			return -1;
	}
}

static void config_color_texture(u32 texture_id, int index, u32 width, u32 height, int sample_count, GLenum format, GLenum internal_format)
{
	if(sample_count > 1) {
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sample_count, internal_format, width, height, GL_FALSE);
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, texture_type(sample_count > 1), texture_id, 0);
}

static void config_depth_texture(u32 texture_id, u32 width, u32 height, int sample_count, GLenum format, GLenum attachment_type)
{
	if(sample_count > 1) {
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sample_count, format, width, height, GL_FALSE);
	} else {
		glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment_type, texture_type(sample_count > 1), texture_id, 0);
}

Framebuffer::Framebuffer(FramebufferFormat fmt)
	: format(fmt)
{
	for(auto& attachment : format.attachments) {
		if(attachment == FramebufferTextureFormat::Depth24Stencil8) {
			depth_attachment = attachment;
		} else {
			color_format_attachments.emplace_back(attachment);
		}
	}

	invalidate();
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &framebuffer_id);
	glDeleteTextures(framebuffer_color_texture_ids.size(), (GLuint*)framebuffer_color_texture_ids.data());
	glDeleteTextures(1, (GLuint const*)&depth_attachment);
}

void Framebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
	glViewport(0, 0, format.width, format.height);
}

void Framebuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::resize(u32 new_width, u32 new_height)
{
	if(new_width == 0 || new_height == 0) {
		DP_ENGINE_WARN("TRIED TO SET ONE OF THE FRAMEBUFFER'S [{0}] DIMENSIONS TO 0", framebuffer_id);
		return;
	}

	format.width  = new_width;
	format.height = new_height;

	invalidate();
}

void Framebuffer::invalidate()
{
	if(framebuffer_id) {
		glDeleteFramebuffers(1, &framebuffer_id);
		glDeleteTextures(framebuffer_color_texture_ids.size(), (GLuint*)framebuffer_color_texture_ids.data());
		glDeleteTextures(1, (GLuint const*)&framebuffer_depth_texture_id);

		framebuffer_color_texture_ids.clear();
		framebuffer_depth_texture_id = 0;
	}

	glGenFramebuffers(1, &framebuffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);

	bool multisample = format.samples > 1;

	if(color_format_attachments.size()) {
		framebuffer_color_texture_ids.resize(color_format_attachments.size());
		glGenTextures(framebuffer_color_texture_ids.size(), framebuffer_color_texture_ids.data());

		for(usize i = 0; i < framebuffer_color_texture_ids.size(); i++) {
			glBindTexture(texture_type(multisample), framebuffer_color_texture_ids[i]);

			switch(color_format_attachments[i]) {
				case FramebufferTextureFormat::RGBA8:
					config_color_texture(framebuffer_color_texture_ids[i], i, format.width, format.height, format.samples, GL_RGBA, GL_RGBA8);
					break;
				case FramebufferTextureFormat::RedInteger:
					config_color_texture(framebuffer_color_texture_ids[i], i, format.width, format.height, format.samples, GL_RGBA, GL_RGBA8);
					break;
				default:
					break;
			}
		}
		glBindTexture(texture_type(multisample), 0);
	}

	if(depth_attachment != FramebufferTextureFormat::None) {
		glGenTextures(1, &framebuffer_depth_texture_id);
		glBindTexture(texture_type(multisample), framebuffer_depth_texture_id);

		switch(depth_attachment) {
			case FramebufferTextureFormat::Depth24Stencil8: {
				config_depth_texture(framebuffer_depth_texture_id, format.width, format.height, format.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
				break;
			}
			default:
				break;
		}
		glBindTexture(texture_type(multisample), 0);
	}

	if(framebuffer_color_texture_ids.size() > 1) {
		ASSERT(framebuffer_color_texture_ids.size() <= 4, "You cannot have more than 4 framebuffer attachments");

		GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(framebuffer_color_texture_ids.size(), buffers);
	} else if(framebuffer_color_texture_ids.empty()) {
		glDrawBuffer(GL_NONE);
	}

	ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int Framebuffer::read_pixel(u32 attachment_index, int x, int y)
{
	ASSERT(attachment_index <= framebuffer_color_texture_ids.size(), "");

	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachment_index);
	int pixelData = 0;
	glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
	return pixelData;
}

u32 Framebuffer::attachment_id(u32 index)
{
	ASSERT(index <= framebuffer_color_texture_ids.size(), "");

	return framebuffer_color_texture_ids[index];
}

void Framebuffer::clear_attachment(u32 attachment, int value)
{
	ASSERT(attachment <= framebuffer_color_texture_ids.size(), "");

	glClearTexImage(framebuffer_color_texture_ids[attachment], 0, to_gl_fbuff_type(color_format_attachments[attachment]), GL_INT, &value);
}

}
