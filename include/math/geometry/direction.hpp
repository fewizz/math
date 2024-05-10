#pragma once

#include <__type/is_base.hpp>

namespace math::geometry {

	struct direction_marker{};

	template<typename Type>
	concept direction = base_of<Type, math::geometry::direction_marker>;

}