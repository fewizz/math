#pragma once

#include "ray_intersection_base.hpp"
#include "ray_plane_intersection_base.hpp"
#include "../triangle.hpp"

namespace math {

template<math::point Point, math::triangle Triangle>
int is_point_outside_triangle(Point p, Triangle t) {
	using namespace math;
	auto n = normal(t);

	if(dot(cross(t[1] - t[0], p - t[0]), n) < 0) return 1;
	if(dot(cross(t[2] - t[1], p - t[1]), n) < 0) return 2;
	if(dot(cross(t[0] - t[2], p - t[2]), n) < 0) return 3;

	return 0;
}

template<math::ray Ray, math::triangle Triangle, typename Dist>
struct ray_triangle_intersection : ray_intersection_base<Ray, Triangle, Dist> {

	ray_triangle_intersection(Ray ray, Triangle triangle)
		: ray_intersection_base<Ray, Triangle, Dist>{ ray, triangle, [&]() -> std::optional<Dist> {
			math::ray_plane_intersection plane_intersection{ ray, triangle };

			if(plane_intersection && !is_point_outside_triangle(plane_intersection.position(), triangle))
				return { plane_intersection.distance() };
			return {};
		}() }
	{}
};

}