#pragma once

#include "ray_base.hpp"
#include "ray_plane.hpp"
#include "../triangle.hpp"

namespace math {

template<math::point Point, math::triangle Triangle>
int is_point_outside_triangle(Point p, Triangle t) {
	using namespace math;
	auto n = normal(t);

	auto p0 = vertex<0>(t);
	auto p1 = vertex<1>(t);
	auto p2 = vertex<2>(t);

	if(dot(cross(p1 - p0, p - p0), n) < 0) return 1;
	if(dot(cross(p2 - p1, p - p1), n) < 0) return 2;
	if(dot(cross(p0 - p2, p - p2), n) < 0) return 3;

	return 0;
}

template<math::ray Ray, math::triangle Triangle, typename Dist = math::length_type<math::origin_type<Ray>>>
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