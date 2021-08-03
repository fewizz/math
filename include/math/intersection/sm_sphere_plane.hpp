#pragma once

#include "sm_sphere_base.hpp"
#include "ray_plane.hpp"
#include "../plane.hpp"

namespace math {

template<math::sm_sphere Sphere, math::plane Plane, typename Dist>
struct sm_sphere_plane_intersection : sm_sphere_intersection_base<Sphere, Plane, Dist> {

	sm_sphere_plane_intersection(Sphere s, Plane p)
		: sm_sphere_intersection_base<Sphere, Plane, Dist>{ s, p, [&]() -> std::optional<Dist> {
			using namespace glm;
			using namespace std;

			auto i = ray_plane_intersection{ s, p };
			if(!i) return {};

			float cos0 = abs(dot(i.normal(), math::direction(s)));
			return { i.distance() - (math::radius(s) / cos0 ) };
		}() }
	{}

};

}