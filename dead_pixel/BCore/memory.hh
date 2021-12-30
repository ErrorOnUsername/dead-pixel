#pragma once
#include <memory>

namespace DP {

template<typename T>
using RefPtr = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr RefPtr<T> make_ref_ptr(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
using OwnPtr = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr OwnPtr<T> make_own_ptr(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

}
