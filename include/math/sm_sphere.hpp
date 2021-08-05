#pragma once

#include "point.hpp"
#include "radius.hpp"
#include "origin.hpp"
#include "direction.hpp"
#include <type_traits>

namespace math {

template<typename T>
concept sm_sphere =
	has_radius<T>
	&& has_origin<T>
	&& has_direction<T>
;

template<math::point P, math::vector V>
struct sm_sphere_by_origin_direction_radius {
	using radius_type = decltype(math::length(std::remove_cvref_t<V>{}));

	P origin;
	P direction;
	radius_type radius;

	sm_sphere_by_origin_direction_radius(P p, V v, radius_type r)
		: origin { p }, direction{ v }, radius{ r }
	{}

	friend auto origin(sm_sphere_by_origin_direction_radius s) { return s.origin; }
	friend auto direction(sm_sphere_by_origin_direction_radius s) { return s.direction; }
	friend auto radius(sm_sphere_by_origin_direction_radius s) { return s.radius; }
};

}