#pragma once

#include <cstdint>
#include "vector.hpp"

namespace math {

template<typename T, std::size_t Size, typename E>
concept point = math::vector<T, Size, E>;

}