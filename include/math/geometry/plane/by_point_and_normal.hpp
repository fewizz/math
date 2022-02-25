#pragma once

#include "../vector.hpp"
#include "../direction.hpp"

namespace math::geometry {

	template<math::geometry::vector Point, math::geometry::direction Normal>
	struct plane_by_point_and_normal {
		Point point;
		Normal normal;
	};

}