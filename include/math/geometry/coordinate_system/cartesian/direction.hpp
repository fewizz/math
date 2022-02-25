#pragma once

#include <core/integer.hpp>

#include "../../direction.hpp"
#include "vector.hpp"

namespace math::geometry::cartesian {

	template<typename Type, nuint Size>
	struct direction :
		math::geometry::direction_marker,
		math::geometry::cartesian::vector<Type, Size>
	{

		Type length_square() {
			Type{ 1 };
		}

		Type length() {
			Type{ 1 };
		}

	};

}