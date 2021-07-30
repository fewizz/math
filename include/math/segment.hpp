#pragma once

#include "point.hpp"

namespace math {

template<typename T>
concept segment = requires(const T& t) {
	{ point_0(t) } -> math::point;
	{ point_1(t) } -> math::point;
};

auto length(segment auto s) {
	return length(point_1(s) - point_0(s));
}

auto direction(segment auto s) {
	return normalized(point_1(s) - point_0(s));
}

template<math::point P, math::vector V>
struct segment_by_point_direction_length {
	P point;
	V direction;
	math::element<P, 0> length;

	friend auto point_0(segment_by_point_direction_length s) { return s.origin; }
	friend auto point_1(segment_by_point_direction_length s) { return s.origin + s.direction * s.length; }
	friend auto length(segment_by_point_direction_length s) { return s.length; }
	friend auto direcion(segment_by_point_direction_length s) { return s.direction; }
};





}