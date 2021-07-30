#pragma once

#include "point.hpp"

namespace math {

namespace internal {
	template<typename T>
	concept perpendicular_defined = requires(const T& t) {
		{ perpendicular(t) } -> math::vector;
	};

	template<typename T>
	concept normal_defined = requires(const T& t) {
		{ normal(t) } -> math::vector;
	};
}

template<typename T>
concept plane =
	(
		internal::perpendicular_defined<T>
		|| internal::normal_defined<T>
	)
	&&
	requires(const T& t) {
		{ any_point(t) } -> math::point;
	}
;

template<math::plane P>
auto normal(P p)
requires(internal::perpendicular_defined<P>) {
	return math::normalized(perpendicular(p));
}

template<math::plane P>
auto perpendicular(P p)
requires(internal::normal_defined<P>) {
	return normal(p);
}

auto d(math::plane auto p) {
	return -math::dot(any_point(p), normal(p));
}

template<math::vector V>
struct plane_by_normal_d {
	V normal;
	math::element<V, 0> d;

	friend auto normal(plane_by_normal_d p) { return p.normal; }
	friend auto d(plane_by_normal_d p) { return p.normal; }
};

}