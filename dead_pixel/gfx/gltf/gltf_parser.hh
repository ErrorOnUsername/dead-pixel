#pragma once

#include <core/json_parser.hh>
#include <gfx/gltf/gltf_spec.hh>

namespace DP {

struct GLTFParser {
	u8* file_data;

	u8*   binary_chunk_raw;
	usize binary_chunck_size;

	JSONValue json_root_obj;

	GLTFParser(char const* filepath);
	~GLTFParser();

	GLBHeader* get_file_header();

	ParsedGLTFFile parse();
	void parse_meshes(ParsedGLTFFile& out);
};

}
