#pragma once

#include "point.hpp"
#include "normal.hpp"
#include "perpendicular.hpp"
#include "has_any_point.hpp"
#include <glm/vec3.hpp>
#include "distance_to_center.hpp"

namespace math {

/*template<typename T>
concept has_d_for_normal = requires(T&& t) {
	d_for_normal(std::forward<T>(t));
};*/

template<typename T>
concept has_d_for_perpendicular = requires(T&& t) {
	d_for_perpendicular(std::forward<T>(t));
};

template<typename T>
concept plane =
	math::has_distance_to_center<T>
	&&
	(math::has_normal<T> || math::has_perpendicular<T>)
;

/*template<typename T>
requires(math::has_any_point<T> && math::has_normal<T>)
auto d_for_normal(T&& p) {
	return -math::dot(any_point(p), math::normal(std::forward<T>(p)));
}

template<typename T>
requires(math::has_perpendicular<T> && math::has_d_for_perpendicular<T>)
auto d_for_normal(T p) {
	return d_for_perpendicular(p) / length(math::perpendicular(p));
}*/

template<math::vector V, typename D = math::element_type<V, 0>>
struct plane_by_normal_and_distance_to_center {
	V normal;
	D d;

	plane_by_normal_and_distance_to_center(V n, D d) : normal{ n }, d{ d } {}

	friend V normal(plane_by_normal_and_distance_to_center p) { return p.normal; }
	friend D distance_to_center(plane_by_normal_and_distance_to_center p) { return p.d; }
};

template<math::vector V, typename D = math::element_type<V, 0>>
struct plane_by_perpendicular_and_distance_to_center {
	V perpendicular;
	D d;

	plane_by_perpendicular_and_distance_to_center(V n, D d) : perpendicular{ n }, d{ d } {}

	friend V perpendicular(plane_by_perpendicular_and_distance_to_center p) { return p.perpendicular; }
	friend D distance_to_center(plane_by_perpendicular_and_distance_to_center p) { return p.d; }
};

}