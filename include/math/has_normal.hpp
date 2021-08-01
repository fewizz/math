#pragma once

#include "vector.hpp"

namespace math {

template<typename T>
concept has_normal = requires(const T& t) {
	{ normal(t) } -> math::vector;
};

}