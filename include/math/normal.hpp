#pragma once

#include "has_perpendicular.hpp"

namespace math {

template<math::has_perpendicular T>
auto normal(T t) {
	return normalized(perpendicular(t));
}


}