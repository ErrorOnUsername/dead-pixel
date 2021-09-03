#pragma once
#include <memory>

namespace DP {
template<typename T>
using unique_ptr = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr unique_ptr<T> create_unique_ptr(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using shared_ptr = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr shared_ptr<T> create_shared_ptr(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}
}