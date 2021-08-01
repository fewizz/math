#pragma once

#include "vector.hpp"

namespace math {

template<typename T>
concept has_perpendicular = requires(const T& t) {
	{ perpendicular(t) } -> math::vector;
};

}