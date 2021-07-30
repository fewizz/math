#pragma once

#include "point.hpp"

namespace math {

template<typename T>
concept ray = requires(const T& t) {
	origin(t);
	direction(t);
};

template<math::point V>
struct ray_by_point_and_direction {
	V origin;
	V direction;
};

template<math::point V> auto origin(ray_by_point_and_direction<V> r) { return r.origin; }
template<math::point V> auto direction(ray_by_point_and_direction<V> r) { return r.direction; }

}