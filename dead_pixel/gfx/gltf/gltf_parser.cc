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

	i64 vert_accessor   = -1;
	i64 normal_accessor = -1;
	i64 uv_accessor     = -1;
	i64 idx_accessor    = -1;

	// Get accessor indices
	{
		// TODO: Make macros for this trash
		//       Or just a nice api to deserialize it (templates maybe?)
		JSON_READ_OBJ_PROP(meshes_arr, json_root_obj, "meshes", JSON_MEMBER_TYPE_ARRAY);
		ASSERT(meshes_arr.value.arr->elems.size() > 0, "glTF member 'meshes' is empty!");

		JSON_READ_ARRAY_ELEM(mesh0_obj, meshes_arr, 0, JSON_MEMBER_TYPE_OBJECT);
		JSON_READ_OBJ_PROP(prims_arr, mesh0_obj, "primitives", JSON_MEMBER_TYPE_ARRAY);
		ASSERT(prims_arr.value.arr->elems.size() > 0, "glTF member 'primitives' is empty!");

		JSON_READ_ARRAY_ELEM(prim0_obj, prims_arr, 0, JSON_MEMBER_TYPE_OBJECT);
		JSON_READ_OBJ_PROP(prim0_attr_obj, prim0_obj, "attributes", JSON_MEMBER_TYPE_OBJECT);

		// Accessor indices

		JSON_READ_OBJ_PROP(prim0_pos_acc_val, prim0_attr_obj, "POSITION", JSON_MEMBER_TYPE_NUMBER_I);
		vert_accessor = prim0_pos_acc_val.value.int64;

		JSON_READ_OBJ_PROP(prim0_norm_acc_val, prim0_attr_obj, "NORMAL", JSON_MEMBER_TYPE_NUMBER_I);
		normal_accessor = prim0_norm_acc_val.value.int64;

		JSON_READ_OBJ_PROP(prim0_uv_acc_val, prim0_attr_obj, "TEXCOORD_0", JSON_MEMBER_TYPE_NUMBER_I);
		uv_accessor = prim0_uv_acc_val.value.int64;

		JSON_READ_OBJ_PROP(prim0_idx_acc_val, prim0_obj, "indices", JSON_MEMBER_TYPE_NUMBER_I);
		idx_accessor = prim0_idx_acc_val.value.int64;
	}

	i64 vert_buff_view         = -1;
	i64 vert_buff_comp_count   = -1;
	i64 normal_buff_view       = -1;
	i64 normal_buff_comp_count = -1;
	i64 uv_buff_view           = -1;
	i64 uv_buff_comp_count     = -1;
	i64 idx_buff_view          = -1;
	i64 idx_buff_comp_count    = -1;

	{
		JSON_READ_OBJ_PROP(acc_arr, json_root_obj, "accessors", JSON_MEMBER_TYPE_ARRAY);
		ASSERT_FMT(acc_arr.value.arr->elems.size() >= 4, "glTF member 'accessors' is length {}, needed 4!", acc_arr.value.arr->elems.size());

		//
		// Get vertex buffer view and verify type
		//

		JSON_READ_ARRAY_ELEM(vert_acc_obj, acc_arr, vert_accessor, JSON_MEMBER_TYPE_OBJECT);

		JSON_READ_OBJ_PROP(vert_ty_str, vert_acc_obj, "type", JSON_MEMBER_TYPE_STRING);
		ASSERT_FMT(vert_ty_str.str == "VEC3", "type for buffer view at 'accessors[{}]' is supposed to be 'VEC3', but got: '{}'", vert_accessor, vert_ty_str.str);

		JSON_READ_OBJ_PROP(vert_buff_view_n, vert_acc_obj, "bufferView", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(vert_buff_comp_count_n, vert_acc_obj, "count", JSON_MEMBER_TYPE_NUMBER_I);

		vert_buff_view       = vert_buff_view_n.value.int64;
		vert_buff_comp_count = vert_buff_comp_count_n.value.int64;

		//
		// Get normal buffer view and verify type
		//

		JSON_READ_ARRAY_ELEM(normal_acc_obj, acc_arr, normal_accessor, JSON_MEMBER_TYPE_OBJECT);

		JSON_READ_OBJ_PROP(norm_ty_str, normal_acc_obj, "type", JSON_MEMBER_TYPE_STRING);
		ASSERT_FMT(norm_ty_str.str == "VEC3", "type for buffer view at 'accessors[{}]' is supposed to be 'VEC3', but got: '{}'", normal_accessor, norm_ty_str.str);

		JSON_READ_OBJ_PROP(normal_buff_view_n, normal_acc_obj, "bufferView", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(normal_buff_comp_count_n, normal_acc_obj, "count", JSON_MEMBER_TYPE_NUMBER_I);

		normal_buff_view       = normal_buff_view_n.value.int64;
		normal_buff_comp_count = normal_buff_comp_count_n.value.int64;

		//
		// Get uv buffer view and verify type
		//

		JSON_READ_ARRAY_ELEM(uv_acc_obj, acc_arr, uv_accessor, JSON_MEMBER_TYPE_OBJECT);

		JSON_READ_OBJ_PROP(uv_ty_str, uv_acc_obj, "type", JSON_MEMBER_TYPE_STRING);
		ASSERT_FMT(uv_ty_str.str == "VEC2", "type for buffer view at 'accessors[{}]' is supposed to be 'VEC3', but got: '{}'", uv_accessor, uv_ty_str.str);

		JSON_READ_OBJ_PROP(uv_buff_view_n, uv_acc_obj, "bufferView", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(uv_buff_comp_count_n, uv_acc_obj, "count", JSON_MEMBER_TYPE_NUMBER_I);

		uv_buff_view       = uv_buff_view_n.value.int64;
		uv_buff_comp_count = uv_buff_comp_count_n.value.int64;

		//
		// Get index buffer view and verify type
		//

		JSON_READ_ARRAY_ELEM(idx_acc_obj, acc_arr, idx_accessor, JSON_MEMBER_TYPE_OBJECT);

		JSON_READ_OBJ_PROP(idx_ty_str, idx_acc_obj, "type", JSON_MEMBER_TYPE_STRING);
		ASSERT_FMT(idx_ty_str.str == "VEC2", "type for buffer view at 'accessors[{}]' is supposed to be 'VEC3', but got: '{}'", uv_accessor, idx_ty_str.str);

		JSON_READ_OBJ_PROP(idx_buff_view_n, idx_acc_obj, "bufferView", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(idx_buff_comp_count_n, idx_acc_obj, "count", JSON_MEMBER_TYPE_NUMBER_I);

		idx_buff_view       = idx_buff_view_n.value.int64;
		idx_buff_comp_count = idx_buff_comp_count_n.value.int64;
	}

	struct BufferView {
		i64 buffer = -1;
		i64 byte_len = -1;
		i64 byte_offset = -1;
	};

	BufferView vert_view { };
	BufferView norm_view { };
	BufferView uv_view   { };
	BufferView idx_view  { };

	{
		JSON_READ_OBJ_PROP(buffer_views_arr, json_root_obj, "bufferViews", JSON_MEMBER_TYPE_ARRAY);

		JSON_READ_ARRAY_ELEM(v_view_obj, buffer_views_arr, vert_buff_view, JSON_MEMBER_TYPE_OBJECT);
		JSON_READ_OBJ_PROP(v_buff, v_view_obj, "buffer", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(v_byte_len, v_view_obj, "byteLength", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(v_byte_offset, v_view_obj, "byteOffset", JSON_MEMBER_TYPE_NUMBER_I);

		vert_view.buffer      = v_buff.value.int64;
		vert_view.byte_len    = v_byte_len.value.int64;
		vert_view.byte_offset = v_byte_offset.value.int64;

		JSON_READ_ARRAY_ELEM(n_view_obj, buffer_views_arr, normal_buff_view, JSON_MEMBER_TYPE_OBJECT);
		JSON_READ_OBJ_PROP(n_buff, n_view_obj, "buffer", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(n_byte_len, n_view_obj, "byteLength", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(n_byte_offset, n_view_obj, "byteOffset", JSON_MEMBER_TYPE_NUMBER_I);

		norm_view.buffer      = n_buff.value.int64;
		norm_view.byte_len    = n_byte_len.value.int64;
		norm_view.byte_offset = n_byte_offset.value.int64;

		JSON_READ_ARRAY_ELEM(u_view_obj, buffer_views_arr, uv_buff_view, JSON_MEMBER_TYPE_OBJECT);
		JSON_READ_OBJ_PROP(u_buff, u_view_obj, "buffer", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(u_byte_len, u_view_obj, "byteLength", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(u_byte_offset, u_view_obj, "byteOffset", JSON_MEMBER_TYPE_NUMBER_I);

		uv_view.buffer      = u_buff.value.int64;
		uv_view.byte_len    = u_byte_len.value.int64;
		uv_view.byte_offset = u_byte_offset.value.int64;

		JSON_READ_ARRAY_ELEM(i_view_obj, buffer_views_arr, idx_buff_view, JSON_MEMBER_TYPE_OBJECT);
		JSON_READ_OBJ_PROP(i_buff, i_view_obj, "buffer", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(i_byte_len, i_view_obj, "byteLength", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(i_byte_offset, i_view_obj, "byteOffset", JSON_MEMBER_TYPE_NUMBER_I);

		idx_view.buffer      = i_buff.value.int64;
		idx_view.byte_len    = i_byte_len.value.int64;
		idx_view.byte_offset = i_byte_offset.value.int64;
	}

	{
		i64 v_buffer_len = -1;
		i64 n_buffer_len = -1;
		i64 u_buffer_len = -1;
		i64 i_buffer_len = -1;

		JSON_READ_OBJ_PROP(buffers_arr, json_root_obj, "buffers", JSON_MEMBER_TYPE_ARRAY);

		JSON_READ_ARRAY_ELEM(v_buff, buffers_arr, vert_view.buffer, JSON_MEMBER_TYPE_OBJECT);
		JSON_READ_ARRAY_ELEM(n_buff, buffers_arr, norm_view.buffer, JSON_MEMBER_TYPE_OBJECT);
		JSON_READ_ARRAY_ELEM(u_buff, buffers_arr, uv_view.buffer, JSON_MEMBER_TYPE_OBJECT);
		JSON_READ_ARRAY_ELEM(i_buff, buffers_arr, idx_view.buffer, JSON_MEMBER_TYPE_OBJECT);

		JSON_READ_OBJ_PROP(v_buff_len_val, v_buff, "byteLength", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(n_buff_len_val, n_buff, "byteLength", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(u_buff_len_val, u_buff, "byteLength", JSON_MEMBER_TYPE_NUMBER_I);
		JSON_READ_OBJ_PROP(i_buff_len_val, i_buff, "byteLength", JSON_MEMBER_TYPE_NUMBER_I);

		v_buffer_len = v_buff_len_val.value.int64;
		n_buffer_len = n_buff_len_val.value.int64;
		u_buffer_len = u_buff_len_val.value.int64;
		i_buffer_len = i_buff_len_val.value.int64;
	}

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
