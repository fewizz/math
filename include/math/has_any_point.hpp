#pragma once

#include "point.hpp"

namespace math {

template<typename T>
concept has_any_point = requires(const T& t) {
	any_point(t) -> math::point;
};

}