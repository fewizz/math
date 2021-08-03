#pragma once

#include "point.hpp"
//#include "normal.hpp"
#include "vertex.hpp"

namespace math {

template<typename T>
concept triangle = math::has_vertex<T, 0> && math::has_vertex<T, 1> && math::has_vertex<T, 2>;

template<math::point V>
struct triangle_by_points {
	V v0;
	V v1;
	V v2;

	constexpr triangle_by_points(V p0, V p1, V p2)
		: v0{ p0 }, v1{ p1 }, v2{ p2 }
	{}

	template<std::size_t Index>
	requires(Index >= 0 && Index < 3)
	constexpr V vertex() const {
		if constexpr(Index == 0) return v0;
		if constexpr(Index == 1) return v1;
		return v2;
	}
	//friend V point_1(triangle_by_points t) { return t.point_1; }
	//friend V point_2(triangle_by_points t) { return t.point_2; }
};

/*template<math::triangle T>
auto perpendicular(T t) {
	auto p0 = point_0(t);
	return math::cross(point_1(t) - p0, point_2(t) - p0);
}

template<math::triangle T>
auto d_for_perpendicular(T t) {
	return math::dot(point_0(t), perpendicular(t));
}*/

}