#pragma once
#include <unordered_map>
#include <vector>

#include <core/arena_allocator.hh>
#include <core/types.hh>

namespace DP {

#define JSON_MEMBER_TYPE_OBJECT   0
#define JSON_MEMBER_TYPE_ARRAY    1
#define JSON_MEMBER_TYPE_NUMBER_I 2
#define JSON_MEMBER_TYPE_NUMBER_F 3
#define JSON_MEMBER_TYPE_STRING   4
#define JSON_MEMBER_TYPE_BOOL     5
#define JSON_MEMBER_TYPE_NULL     6

struct JSONArray;
struct JSONObject;

struct JSONValue {
	i32 type;

	std::string str;

	union {
		JSONObject* obj;
		JSONArray*  arr;

		double f64;

		i32 int32;
		u32 uint32;
		i64 int64;
		u64 uint64;

		bool b8;
	} value;
};

struct JSONArray {
	std::vector<JSONValue> elems;
};

struct JSONObject {
	std::unordered_map<std::string, JSONValue> props;
};


struct JSONParser {
	u8*   raw_file_data;
	usize raw_data_size;

	usize index;

	JSONParser(char const* path);
	JSONParser(u8* raw_file_data, usize raw_data_size);

	std::string parse_string_impl();

	JSONValue parse();
	JSONValue parse_data();

	JSONValue parse_object();
	JSONValue parse_array();
	JSONValue parse_string();
	JSONValue parse_number();
	JSONValue parse_true();
	JSONValue parse_false();
	JSONValue parse_null();

	void consume_whitespace();

	bool at_eof();
	char current();
	char peek(usize offset);
};

}
