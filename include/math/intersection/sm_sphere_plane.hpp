#pragma once

#include "sm_sphere_base.hpp"
#include "ray_plane.hpp"
#include "../plane.hpp"

namespace math {

template<math::sm_sphere Sphere, math::plane Plane, typename Dist = math::length_type<math::origin_type<Sphere>>>
struct sm_sphere_plane_intersection : sm_sphere_intersection_base<Sphere, Plane, Dist> {

	sm_sphere_plane_intersection(Sphere s, Plane p)
		: sm_sphere_intersection_base<Sphere, Plane, Dist>{ s, p, [&]() -> std::optional<Dist> {
			auto i = math::ray_plane_intersection{ s, p };
			if(!i) return {};

			float cos0 = std::abs(math::dot(i.opposite_normal(), math::direction(s)));
			return { i.distance() - (math::radius(s) / cos0 ) };
		}() }
	{}

};

}