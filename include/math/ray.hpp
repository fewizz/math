#pragma once

#include "origin.hpp"
#include "direction.hpp"

namespace math {

template<typename T>
concept ray = math::has_origin<T> && math::has_direction<T>;

template<math::point P, math::vector V>
struct ray_by_point_and_direction {
	P origin;
	V direction;

	ray_by_point_and_direction(P p, V d) : origin{ p }, direction{ d } {}

	friend P origin(ray_by_point_and_direction r) { return r.origin; }
	friend V direction(ray_by_point_and_direction r) { return r.direction; }
};

}