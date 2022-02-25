#pragma once

#include <core/meta/type/is_base.hpp>

namespace math::geometry {

	struct ray_marker{};

	template<typename Ray>
	concept ray = type::is_base<math::geometry::ray_marker>::for_type<Ray>;

}