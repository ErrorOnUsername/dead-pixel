#pragma once

#include <core/types.hh>
#include <core/assert.hh>

namespace DP {

struct ArenaAllocator {
	usize capacity;
	usize used_bytes;

	u8* base;
	u8* head;

	ArenaAllocator(usize capacity)
		: capacity(capacity)
		, used_bytes(0)
		, base(nullptr)
		, head(nullptr)
	{
		base = new u8[capacity];
		head = base;
	}

	~ArenaAllocator()
	{
		delete base;
	}

	void* alloc(usize size)
	{
		ASSERT_FMT(used_bytes + size <= capacity, "Arena of size {} is full!!", capacity);

		std::memset(head, 0, size);

		void* start = (void*)head;

		head       += size;
		used_bytes += size;

		return start;
	}

	void clear()
	{
		head = base;
		used_bytes = 0;
	}
};

}
