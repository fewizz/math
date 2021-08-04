#pragma once

#include "sm_sphere_base.hpp"
#include "ray_plane.hpp"
#include "../plane.hpp"

namespace math {

template<math::sm_sphere Sphere, math::plane Plane, typename Dist = math::length_type<math::origin_type<Sphere>>>
struct sm_sphere_plane_intersection : sm_sphere_intersection_base<Sphere, Plane, Dist> {

	sm_sphere_plane_intersection(Sphere s, Plane p)
		: sm_sphere_intersection_base<Sphere, Plane, Dist>{ s, p}
	{
		auto i = math::ray_plane_intersection{ s, p };
		if(!i) return;

		auto on = i.opposite_normal();
		float cos0 = std::abs(math::dot(on, math::direction(s)));
		this->result = i.distance() - (math::radius(s) / cos0 );
		this->normal = on;
	}
	

};

}