#pragma once

#include <core/meta/type/is_base.hpp>

namespace math::geometry {

	struct plane_marker{};

	template<typename Type>
	concept plane = type::is_base<math::geometry::plane_marker>::for_type<Type>;

}