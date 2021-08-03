#pragma once

#include "point.hpp"

namespace math {

template<typename T>
concept sphere = requires(const T& t) {
	origin(t);
	radius(t);
};


template<math::point P>
struct sphere_by_point_radius {
	P origin;
	math::element_type<P, 0> radius;

	friend P origin(sphere_by_point_radius s) { return s.origin; }
	friend auto radius(sphere_by_point_radius s) { return s.radius; }
};

}