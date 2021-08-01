#pragma once

#include "point.hpp"

namespace math {

template<typename T>
concept has_direction = requires(const T& t) {
	{ direction(t) } -> math::vector;
};

}