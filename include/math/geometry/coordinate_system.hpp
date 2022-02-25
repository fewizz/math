#pragma once

#include <core/meta/type/is_base.hpp>

namespace math::geometry {

	struct coordinate_system_marker{};

	template<typename Type>
	concept direction = type::is_base<math::geometry::coordinate_system_marker>::for_type<Type>;

}