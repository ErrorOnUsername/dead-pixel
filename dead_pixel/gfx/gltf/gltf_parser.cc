#include "gltf_parser.hh"

#include <core/file_utils.hh>
#include <gfx/gltf/gltf_spec.hh>

namespace DP {

GLTFParser::GLTFParser(char const* filepath)
{
	file_data = FileUtils::read_file_from_relative_path(filepath);

	GLBHeader* gltf_header = get_file_header();
	u32        data_length = gltf_header->length;

	// Parse JSON data

	GLBChunk* json_chunk_info = (GLBChunk*)(file_data + 12);
	ASSERT(json_chunk_info->chunk_type == GLB_CHUNK_TYPE_JSON, "Missing JSON chunk");

	u8*        json_raw  = &json_chunk_info->chunk_data_start;
	usize      json_size = json_chunk_info->chunk_length;
	JSONParser parser(json_raw, json_size);

	json_root_obj = parser.parse();
	ASSERT(json_root_obj.type == JSON_MEMBER_TYPE_OBJECT, "Missing root object!");

	// Locate binary data

	GLBChunk* binary_chunk_info = (GLBChunk*)(file_data + 12 + 8 + json_chunk_info->chunk_length);
	ASSERT(binary_chunk_info->chunk_type == GLB_CHUNK_TYPE_BINARY, "Missing BIN chunk");

	binary_chunk_raw   = &binary_chunk_info->chunk_data_start;
	binary_chunck_size = binary_chunk_info->chunk_length;
}

GLTFParser::~GLTFParser()
{
	free(file_data);
}

ParsedGLTFFile GLTFParser::parse()
{
	ParsedGLTFFile file;



	return file;
}

GLBHeader* GLTFParser::get_file_header()
{
	GLBHeader* header = (GLBHeader*)file_data;
	ASSERT_FMT(header->magic == GLB_MAGIC, "Invalid GLB magic wanted {:x} got {:x}", GLB_MAGIC, header->magic);

	return header;
}

void GLTFParser::parse_meshes(ParsedGLTFFile& out)
{
}

}
