#pragma once

#include <core/meta/type/is_base.hpp>

namespace math::geometry {

	struct direction_marker{};

	template<typename Type>
	concept direction = type::is_base<math::geometry::direction_marker>::for_type<Type>;

}