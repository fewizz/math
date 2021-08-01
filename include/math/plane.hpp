#pragma once

#include "point.hpp"
#include "has_normal.hpp"
#include "normal.hpp"
#include "has_any_point.hpp"

namespace math {

template<typename T>
concept has_d_for_normal = requires(const T& t) {
	d_for_normal(t);
};

template<typename T>
concept has_d_for_perpendicular = requires(const T& t) {
	d_for_perpendicular(t);
};

template<typename T>
concept plane =
	math::has_normal<T> && math::has_d_for_normal<T>
	||
	math::has_perpendicular<T> && math::has_d_for_perpendicular<T>
;

template<typename T>
requires(math::has_any_point<T> && math::has_normal<T>)
auto d_for_normal(T p) {
	return -math::dot(any_point(p), normal(p));
}

template<typename T>
requires(math::has_perpendicular<T> && math::has_d_for_perpendicular<T>)
auto d_for_normal(T p) {
	return d_for_perpendicular(p) / length(perpendicular(p));
}

template<math::vector V, typename D = math::element<V, 0>>
struct plane_by_normal_d {
	V normal;
	D d;

	plane_by_normal_d(V n, D d) : normal{ n }, d{ d } {}

	friend V normal(plane_by_normal_d p) { return p.normal; }
	friend D d_for_normal(plane_by_normal_d p) { return p.d; }
};

template<math::vector V, typename D = math::element<V, 0>>
struct plane_by_perpendicular_d {
	V perpendicular;
	D d;

	plane_by_perpendicular_d(V n, D d) : perpendicular{ n }, d{ d } {}

	friend V perpendicular(plane_by_perpendicular_d p) { return p.perpendicular; }
	friend D d_for_perpendicular(plane_by_perpendicular_d p) { return p.d; }
};

}