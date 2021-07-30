#pragma once

#include "point.hpp"

namespace math {

template<typename T>
concept sm_sphere = requires(const T& t) {
	{ origin(t) } -> math::point;
	{ direction(t) } -> math::vector;
	radius(t);
};

template<math::point P, math::vector V>
struct sm_sphere_by_origin_direction_radius {
	P origin;
	P direction;
	math::element<P, 0> radius;

	friend auto origin(sm_sphere_by_origin_direction_radius s) { return s.origin; }
	friend auto direction(sm_sphere_by_origin_direction_radius s) { return s.direction; }
	friend auto radius(sm_sphere_by_origin_direction_radius s) { return s.radius; }
};

}