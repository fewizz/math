#pragma once

#include "../ray.hpp"
#include "../vector.hpp"
#include "../direction.hpp"

namespace math::geometry {

	template<math::geometry::vector Origin, math::geometry::direction Direction>
	struct ray_by_origin_and_direction : math::geometry::ray_marker {
		Origin origin;
		Direction direction;
	};

}