#pragma once

#include "../plane.hpp"
#include "../direction.hpp"

namespace math::geometry {

	template<math::geometry::direction Normal, typename DistanceToOrigin>
	struct plane_by_normal_and_distance : math::geometry::plane_marker {
		Normal normal;
		DistanceToOrigin distance_to_origin;
	};

}