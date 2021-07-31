#pragma once

#include "point.hpp"

namespace math {

template<typename T>
concept plane =
	requires(const T& t) {
		{ perpendicular(t) } -> math::vector;
		{ any_point(t) } -> math::point;
	}
;

template<math::plane P>
auto normal(P p) {
	return math::normalized(perpendicular(p));
}

auto d(math::plane auto p) {
	return -math::dot(any_point(p), normal(p));
}

template<math::vector V>
struct plane_by_normal_d {
	V normal;
	math::element<V, 0> d;

	friend auto perpendicular(plane_by_normal_d p) { return p.normal; }
	friend auto normal(plane_by_normal_d p) { return p.normal; }
	friend auto d(plane_by_normal_d p) { return p.d; }
};

}