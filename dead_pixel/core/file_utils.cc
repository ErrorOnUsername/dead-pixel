#include "file_utils.hh"
#include <cstdio>
#include <cstring>
#include <unistd.h>

#include <core/assert.hh>

namespace DP::FileUtils {

u8* read_file_from_relative_path(char const* rel_path)
{
	char cwd[128];
	getcwd(cwd, 128);

	usize cwd_len = strlen(cwd);
	usize rel_len = strlen(rel_path);

	char abs_path[256];
	strncpy(abs_path, cwd, cwd_len);

#ifdef _WIN32
	abs_path[cwd_len] = '\\';
#else
	abs_path[cwd_len] = '/';
#endif

	ASSERT(256 - (cwd_len + 1) >= rel_len, "FILE PATH TOO LONG AND DOESN'T FIT IN BUFFER");
	strncpy(&abs_path[cwd_len + 1], rel_path, rel_len);

	abs_path[cwd_len + 1 + rel_len] = 0;

	FILE* file = fopen((char const*)abs_path, "r");
	ASSERT_FMT(file, "Could not find file at path: {0}!!!", rel_path);

	fseek(file, 0, SEEK_END);
	usize size = ftell(file);
	fseek(file, 0, SEEK_SET);

	u8* file_data = (u8*)malloc(size + 1);
	fread(file_data, 1, size + 1, file);
	file_data[size] = 0;
	fclose(file);

	return file_data;
}

}
