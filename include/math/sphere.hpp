#pragma once

#include "point.hpp"
#include "radius.hpp"
#include "origin.hpp"

namespace math {

template<typename T>
concept sphere = math::has_radius<T> && math::has_origin<T>;


template<math::point P, typename R = math::element_type<P, 0>>
struct sphere_by_point_radius {
	P origin;
	R radius;

	friend P origin(sphere_by_point_radius s) { return s.origin; }
	friend auto radius(sphere_by_point_radius s) { return s.radius; }
};

}