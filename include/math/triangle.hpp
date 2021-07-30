#pragma once

#include "point.hpp"

namespace math {

template<typename T>
concept triangle = requires(const T& t) {
	{ point_0(t) } -> math::point;
	{ point_1(t) } -> math::point;
	{ point_2(t) } -> math::point;
};

template<math::point V>
struct triangle_by_points {
	V point_0;
	V point_1;
	V point_2;
};

template<math::point V> auto point_0(triangle_by_points<V> t) { return t.point_0; }
template<math::point V> auto point_1(triangle_by_points<V> t) { return t.point_0; }
template<math::point V> auto point_2(triangle_by_points<V> t) { return t.point_0; }

}