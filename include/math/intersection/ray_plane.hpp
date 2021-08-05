#pragma once

#include "ray_base.hpp"
#include "../plane.hpp"

namespace math {

template<math::ray Ray, math::plane Plane, typename Dist = math::common_element_type<math::origin_type<Ray>>>
struct ray_plane_intersection : ray_intersection_base<Ray, Plane, Dist> {

// P·x + D = 0
// O+L*t = x
// P·(O+L*t) + D = 0
// P·O+tP·L + D = 0
// t = -(D + P·O) / P·L
	ray_plane_intersection(Ray ray, Plane plane)
		: ray_intersection_base<Ray, Plane, Dist>{ ray, plane, [&]() -> std::optional<Dist> {

			auto d = math::direction(ray);
			auto n = math::normal(plane);
			auto nd = dot(n, d);

			if(nd != 0)
				return { -(distance_to_center(plane) + dot(n, origin(ray))) / nd };
			return {};
		}() }
	{}
};

}