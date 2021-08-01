#pragma once

#include "ray_base.hpp"
#include "../plane.hpp"

namespace math {

template<math::ray Ray, math::plane Plane, typename Dist = decltype(d_for_normal(std::declval<Plane>()))>
struct ray_plane_intersection : ray_intersection_base<Ray, Plane, Dist> {

	ray_plane_intersection(Ray ray, Plane plane)
		: ray_intersection_base<Ray, Plane, Dist>{ ray, plane, [&]() -> std::optional<Dist> {
			using namespace math;

			auto nd = dot(normal(plane), direction(ray));

			if(nd != 0)
				return { (d_for_normal(plane) - dot(normal(plane), origin(ray))) / nd };
			return {};
		}() }
	{}
};

}