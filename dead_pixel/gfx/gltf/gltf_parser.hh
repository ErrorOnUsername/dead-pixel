#pragma once

struct ParsedGLTFFile;

struct GLTFParser {
	static ParsedGLTFFile from_file(char const* filepath);
};
