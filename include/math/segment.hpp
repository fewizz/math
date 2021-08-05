#pragma once

#include "point.hpp"
#include "vertex.hpp"

namespace math {

template<typename T>
concept segment = math::vertex_count<T> == 2;

auto length(math::segment auto s) {
	return math::length(math::vertex<1>(s) - math::vertex<0>(s));
}

template<math::point P, math::vector V>
struct segment_by_point_direction_length {
	using length_type = decltype(math::length(V{}));

	P origin;
	V direction;
	length_type length;

	segment_by_point_direction_length(P origin, V direction, length_type length)
		: origin{ origin }, direction{ direction }, length{ length }
	{}

	template<std::size_t Index>
	requires(Index < 2)
	constexpr P vertex() const {
		if constexpr(Index == 0) return origin;
		else return origin + direction * length;
	}

	friend auto length(segment_by_point_direction_length s) { return s.length; }
	friend auto direcion(segment_by_point_direction_length s) { return s.direction; }
};





}