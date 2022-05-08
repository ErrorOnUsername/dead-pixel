#pragma once
#include <functional>

#include <core/types.hh>

namespace DP {

struct UUID {
	static constexpr usize UUID_SIZE_IN_BYTES = 16;

	u8 underlying[UUID_SIZE_IN_BYTES];

	UUID() = default;
	void generate();

	bool operator==(UUID const& other) const
	{
		for(usize i = 0; i < UUID_SIZE_IN_BYTES; i++) {
			if(underlying[i] != other.underlying[i])
				return false;
		}

		return true;
	}

	bool operator==(usize other) const
	{
		for(usize i = 0; i < UUID_SIZE_IN_BYTES; i++) {
			if(underlying[i] != other)
				return false;
		}

		return true;
	}
};

}

template<>
struct std::hash<DP::UUID> {
public:
	usize operator()(DP::UUID const& uuid) const
	{
		usize h0  = std::hash<u64>{}(*((u64*)(&uuid.underlying[0])));
		usize h1  = std::hash<u64>{}(*((u64*)(&uuid.underlying[8])));
		return h0 ^ (h1 << 1);
	}
};
