#pragma once

#include <__type/is_base.hpp>

namespace math::geometry {

	struct coordinate_system_marker{};

	template<typename Type>
	concept direction = base_of<Type, math::geometry::coordinate_system_marker>;

}