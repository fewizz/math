#pragma once

#include "point.hpp"
#include "normal.hpp"

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

	friend auto point_0(triangle_by_points t) { return t.point_0; }
	friend auto point_1(triangle_by_points t) { return t.point_1; }
	friend auto point_2(triangle_by_points t) { return t.point_2; }
};

template<math::triangle T>
auto perpendicular(T t) {
	auto p0 = point_0(t);
	return math::cross(point_1(t) - p0, point_2(t) - p0);
}

}