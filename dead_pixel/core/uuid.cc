#include "uuid.hh"
#include <string.h>
#include <uuid/uuid.h>

namespace DP {

void UUID::generate()
{
	uuid_t id;
	uuid_generate_time(id);
	memcpy(underlying, id, UUID_SIZE_IN_BYTES);
}

}
