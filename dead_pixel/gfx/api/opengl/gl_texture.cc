#include <gfx/texture.hh>

#include <glad/glad.h>
#include <stb_image.h>

#include <core/assert.hh>

namespace DP {

Texture::Texture(u32 width, u32 height)
	: id(0)
	, is_loaded(false)
	, path("CUSTOM TEXTURE (NO PATH)")
	, width(width)
	, height(height)
	, internal_format(GL_RGBA8)
	, data_format(GL_RGBA)
{
	glGenTextures(1, &id);

	glTextureStorage2D(id, 1, internal_format, width, height);

	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture::Texture(char const* path)
	: id(0)
	, is_loaded(false)
	, path(path)
	, width(0)
	, height(0)
	, internal_format(0)
	, data_format(0)
{
	char cwd[128];
	getcwd(cwd, 128);

	usize cwd_len = strlen(cwd);
	usize rel_len = strlen(path);

	char abs_path[256];
	strncpy(abs_path, cwd, cwd_len);

	abs_path[cwd_len] = '/';

	ASSERT(256 - (cwd_len + 1) >= rel_len, "FILE PATH TOO LONG AND DOESN'T FIT IN BUFFER");
	strncpy(&abs_path[cwd_len + 1], path, rel_len);

	abs_path[cwd_len + 1 + rel_len] = 0;

	int real_width, real_height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(abs_path, &real_width, &real_height, &channels, 0);

	if (data) {
		is_loaded = true;

		width = real_width;
		height = real_height;

		GLenum internal_fmt = 0;
		GLenum data_fmt = 0;

		if (channels == 4) {
			internal_fmt = GL_RGBA8;
			data_fmt = GL_RGBA;
		} else if (channels == 3) {
			internal_fmt = GL_RGB8;
			data_fmt = GL_RGB;
		}

		internal_format = internal_fmt;
		data_format = data_fmt;

		ASSERT(internal_fmt & data_fmt, "Format not supported!");

		glGenTextures(1, &id);

		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, internal_fmt, width, height, 0, data_fmt, GL_UNSIGNED_BYTE, data);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::set_data(void *data, u32 size)
{
	u32 bpp = data_format == GL_RGBA ? 4 : 3;
	ASSERT(size == (width * height * bpp), "Incorrect size for dimension data!");
	glTextureSubImage2D(id, 0, 0, 0, width, height, data_format, GL_UNSIGNED_BYTE, data);
}

void Texture::bind(u32 slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
