#include "json_parser.hh"
#include <cstdlib>
#include <sstream>

#include <core/assert.hh>

namespace DP {

// FIXME: All of this should do proper error propagation, not just asserting on everything.

#define DEFAULT_JSON_ARENA_SIZE 4096

JSONParser::JSONParser(char const* path)
	: raw_file_data(nullptr)
	, raw_data_size(0)
	, index(0)
{
	ASSERT(false, "Implement JSON parsing given path");
}

JSONParser::JSONParser(u8* raw_file_data, usize raw_data_size)
	: raw_file_data(raw_file_data)
	, raw_data_size(raw_data_size)
	, index(0)
{
}

static bool is_whitespace(char c)
{
	switch(c) {
		case ' ':
		case '\t':
		case '\v':
		case '\r':
		case '\n':
			return true;
		default:
			return false;
	}
}

JSONValue JSONParser::parse()
{
	JSONValue res = parse_data();
	consume_whitespace();

	ASSERT(at_eof(), "Multiple root objects.... why?");

	return res;
}

JSONValue JSONParser::parse_data()
{
	consume_whitespace();

	switch(current()) {
		case '{':
			return parse_object();
		case '[':
			return parse_array();
		case '"':
			return parse_string();
		case '-':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return parse_number();
		case 't':
			return parse_true();
		case 'f':
			return parse_false();
		case 'n':
			return parse_null();
	}

	ASSERT_FMT(false, "Unexpected Character!! {}", current());

	JSONValue val;
	return val;
}

JSONValue JSONParser::parse_object()
{
	ASSERT(current() == '{', "Object must start with '{'");
	index++;

	JSONObject obj;

	for(;;) {
		consume_whitespace();
		if(current() == '}')
			break;

		std::string name = parse_string_impl();

		consume_whitespace();
		ASSERT(current() == ':', "Expected ':' after object key name");
		index++;

		consume_whitespace();
		JSONValue val = parse_data();
		obj.props[name] = val;

		consume_whitespace();
		if(current() == '}')
			break;

		ASSERT(current() == ',', "Expected ',' or '}' in object declaration");
		index++;

		consume_whitespace();
		ASSERT(current() != '}', "Unexpected '}' in object decoration");
	}

	consume_whitespace();
	ASSERT(current() == '}', "Object must end with '}'");
	index++;

	JSONValue val;
	val.type = JSON_MEMBER_TYPE_OBJECT;
	val.value.obj = new JSONObject(obj);

	return val;
}

JSONValue JSONParser::parse_array()
{
	ASSERT(current() == '[', "Array must start with '['");
	index++;

	JSONArray arr;
	for(;;) {
		consume_whitespace();
		if(current() == ']')
			break;

		JSONValue elem = parse_data();
		arr.elems.push_back(elem);

		consume_whitespace();
		if(current() == ']')
			break;

		ASSERT(current() == ',', "Expected ',' or ']' in list declaration");
		index++;

		consume_whitespace();
		ASSERT(current() != ']', "Unexpected ']' in list decoration");
	}

	consume_whitespace();
	ASSERT(current() == ']', "Array must end with ']'");
	index++;

	JSONValue val;
	val.type      = JSON_MEMBER_TYPE_ARRAY;
	val.value.arr = new JSONArray(arr);

	return val;
}

std::string JSONParser::parse_string_impl()
{
	ASSERT(current() == '"', "String must start with '\"'");
	index++;

	std::stringstream fnl;

	while(current() != '"' && !at_eof()) {
		char c = current();

		if(c != '\\') {
			fnl << c;
			index++;
			continue;
		}

		switch(peek(1)) {
			case '"':
				fnl << '"';
				break;
			case '\\':
				fnl << '\\';
				break;
			case 'n':
				fnl << '\n';
				break;
			case 'r':
				fnl << '\r';
				break;
			case 't':
				fnl << '\t';
				break;
			case 'b':
				fnl << '\b';
				break;
			case 'f':
				fnl << '\f';
				break;
			default:
				ASSERT_FMT(false, "Unknown escape sequence '\\{}'", peek(1));
		}

		index += 2;
	}

	ASSERT(current() == '"', "String must end with '\"'");
	index++;

	return fnl.str();
}

JSONValue JSONParser::parse_string()
{
	std::string str = parse_string_impl();

	JSONValue val;
	val.type = JSON_MEMBER_TYPE_STRING;
	val.str  = str;

	return val;
}

JSONValue JSONParser::parse_number()
{
	std::vector<char> num_buff;

	bool is_float = false;
	bool is_zeros = true;

	for(;;) {
		char c = current();
		if(c == '.') {
			ASSERT(!is_float, "Multiple uses of '.' in number");

			num_buff.push_back(c);
			is_float = true;
			index++;

			continue;
		}

		if(c == '-' || (c >= '0' && c <= '9')) {
			if(c != '-' && c != '0')
				is_zeros = false;

			if(is_float) {
				ASSERT(c != '-', "Unexpected '-' in floating-point literal");
				num_buff.push_back(c);
			} else {
				if(num_buff.size() > 0)
					ASSERT(num_buff.at(0) != '0', "Invalid leading zeros in number literal");

				if(num_buff.size() > 1)
					ASSERT(num_buff.at(0) != '-' && num_buff.at(1) != '0', "Invalid leading zeros in numnber literal");

				num_buff.push_back(c);
			}

			index++;
			continue;
		}

		break;
	}

	if(current() == 'e' || current() == 'E') {
		ASSERT(false, "Parse exponent notation!!");
	}

	if(num_buff.at(0) == '-' && is_zeros) {
		JSONValue val;
		val.type      = JSON_MEMBER_TYPE_NUMBER_F;
		val.value.f64 = -0.0;

		return val;
	}

	std::string_view num_str(num_buff.data(), num_buff.size());

	if(is_float) {
		double f = strtod(num_str.data(), nullptr);
		ASSERT(errno != ERANGE, "Provided float overflows");

		JSONValue val;
		val.type      = JSON_MEMBER_TYPE_NUMBER_F;
		val.value.f64 = f;

		return val;
	} else {
		i64 i = atoll(num_str.data());

		ASSERT(errno != EINVAL, "No conversion could be performed");
		ASSERT(errno != ERANGE, "The value was out of range");

		JSONValue val;
		val.type        = JSON_MEMBER_TYPE_NUMBER_I;
		val.value.int64 = i;

		return val;
	}
}

JSONValue JSONParser::parse_true()
{
	char const* comp = "true";

	int idx = 0;
	while(comp[idx]) {
		ASSERT(!at_eof(), "Unexpected EOF");
		ASSERT(comp[idx++] == raw_file_data[index++], "Unexpected char while parsing true");
	}

	JSONValue val;
	val.type     = JSON_MEMBER_TYPE_BOOL;
	val.value.b8 = true;
	return val;
}

JSONValue JSONParser::parse_false()
{
	char const* comp = "false";

	int idx = 0;
	while(comp[idx]) {
		ASSERT(!at_eof(), "Unexpected EOF");
		ASSERT(comp[idx++] == raw_file_data[index++], "Unexpected char while parsing false");
	}

	JSONValue val;
	val.type     = JSON_MEMBER_TYPE_BOOL;
	val.value.b8 = false;
	return val;
}

JSONValue JSONParser::parse_null()
{
	char const* comp = "null";

	int idx = 0;
	while(comp[idx]) {
		ASSERT(!at_eof(), "Unexpected EOF");
		ASSERT(comp[idx++] == raw_file_data[index++], "Unexpected char while parsing null");
	}

	JSONValue val;
	val.type = JSON_MEMBER_TYPE_NULL;
	return val;
}

void JSONParser::consume_whitespace()
{
	while(is_whitespace(current())) { index++; }
}

bool JSONParser::at_eof()
{
	return index >= raw_data_size;
}

char JSONParser::current()
{
	return raw_file_data[index];
}

char JSONParser::peek(usize offset)
{
	return raw_file_data[index + offset];
}

}
