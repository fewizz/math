#pragma once

#include "point.hpp"

namespace math {

template<typename T>
concept has_origin = requires(const T& t) {
	{ origin(t) } -> math::point;
};

}