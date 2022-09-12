#include "gltf_parser.hh"

#include <core/json_parser.hh>
#include <gfx/gltf/gltf_spec.hh>

namespace DP {

static u32  check_file_header(u8* file_data);
static void identify_chunks(u8* file_data);

ParsedGLTFFile GLTFParser::from_file(const char *filepath)
{
	u8* file_data = nullptr;
	{
		char cwd[128];
		getcwd(cwd, 128);

		usize cwd_len = strlen(cwd);
		usize rel_len = strlen(filepath);

		char abs_path[256];
		strncpy(abs_path, cwd, cwd_len);

#ifdef _WIN32
		abs_path[cwd_len] = '\\';
#else
		abs_path[cwd_len] = '/';
#endif

		ASSERT(256 - (cwd_len + 1) >= rel_len, "FILE PATH TOO LONG AND DOESN'T FIT IN BUFFER");
		strncpy(&abs_path[cwd_len + 1], filepath, rel_len);

		abs_path[cwd_len + 1 + rel_len] = 0;

		FILE* file = fopen((char const*)abs_path, "r");
		ASSERT_FMT(file, "Could not find file at path: {0}!!!", filepath);

		fseek(file, 0, SEEK_END);
		usize size = ftell(file);
		fseek(file, 0, SEEK_SET);

		file_data = (u8*)malloc(size + 1);
		fread(file_data, 1, size, file);
		fclose(file);
	}

	u32 data_length = check_file_header(file_data);
	identify_chunks(file_data);

	GLBChunk* chunk_info = (GLBChunk*)(file_data + 12);

	u8*   json_raw  = &chunk_info->chunk_data_start;
	usize json_size = chunk_info->chunk_length;

	JSONParser parser(json_raw, json_size);

	JSONValue root_obj = parser.parse();
	ASSERT(root_obj.type == JSON_MEMBER_TYPE_OBJECT, "Missing root object!");
	JSONValue const& meshes_arr = root_obj.value.obj->props.at("meshes");
	ASSERT(meshes_arr.type == JSON_MEMBER_TYPE_ARRAY, "Meshes must be an array");
	JSONValue const& mesh0 = meshes_arr.value.arr->elems[0];
	ASSERT(mesh0.type == JSON_MEMBER_TYPE_OBJECT, "meshes[0] must be an object");

	printf("MESH0:\n");
	for(auto const& kv : mesh0.value.obj->props) {
		printf("|-> \"%s\"\n", kv.first.c_str());
	}

	ParsedGLTFFile ret;
	return ret;
}

static u32 check_file_header(u8* file_data)
{
	GLBHeader* header = (GLBHeader*)file_data;

	ASSERT_FMT(header->magic == GLB_MAGIC, "Invalid GLB magic wanted {:x} got {:x}", GLB_MAGIC, header->magic);
	DP_INFO("GLTF Version: {}", header->version);
	return header->length;
}

static void identify_chunks(u8* file_data)
{
	auto type_name = [](u32 type_number) -> char const* {
		switch(type_number) {
			case GLB_CHUNK_TYPE_BINARY:
				return "Binary";
			case GLB_CHUNK_TYPE_JSON:
				return "JSON";
			default:
				return "Unknown";
		}
	};

	GLBChunk* chunk_info = (GLBChunk*)(file_data + 12);
	DP_INFO("\nChunk 1:\n\tType = {}({:X})\n\tLength = {}", type_name(chunk_info->chunk_type), chunk_info->chunk_type, chunk_info->chunk_length);
	GLBChunk* chunk2_info = (GLBChunk*)(file_data + 12 + 8 + chunk_info->chunk_length);
	DP_INFO("\nChunk 2:\n\tType = {}({:X})\n\tLength = {}", type_name(chunk2_info->chunk_type), chunk2_info->chunk_type, chunk_info->chunk_length);
}

}
