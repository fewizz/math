#pragma once

#include <cstdint>
#include "vector.hpp"

namespace math {

template<typename T>
concept point = math::vector<T>;

}