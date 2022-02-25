#pragma once

#include "../ray.hpp"
#include "../plane.hpp"

namespace math::geometry {

	struct ray_plane_intersection_result {
		bool m_success;

		bool success() const { return m_success; }
	};

	// P·x + D = 0
	// O+L*t = x
	// P·(O+L*t) + D = 0
	// P·O+tP·L + D = 0
	// t = -(D + P·O) / P·L
	template<math::geometry::ray Ray, math::geometry::plane Plane, typename Dist>
	ray_plane_intersection_result intersect_ray_plane(Ray ray, Plane plane) {
		auto d = ray.direction;
		auto n = plane.normal;
		auto nd = math::geometry::dot(n, d);

		if(nd != 0)
			return { -(distance_to_center(plane) + dot(n, origin(ray))) / nd };
		return {};
	}

}