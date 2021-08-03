#pragma once

#include "vector.hpp"
#include "triangle.hpp"

namespace math::internal {

template<typename T>
concept has_perpendicular_unqualified = requires(const T& t) {
	{ perpendicular(t) } -> math::vector;
};

template<typename T>
concept has_perpendicular_member = requires(const T& t) {
	{ t.perpendicular() } -> math::vector;
};

struct perpendicular_fn0 {
	template<has_perpendicular_member T>
	constexpr auto operator () (const T& t) const {
		return t.perpendicular();
	}

	template<has_perpendicular_unqualified T>
	constexpr auto operator () (const T& t) const {
		return perpendicular(t);
	}

	template<math::triangle T>
	constexpr auto operator () (const T& t) const {
		auto v0 = math::vertex<0>(t);
		auto v1 = math::vertex<1>(t);
		auto v2 = math::vertex<2>(t);

		return math::cross(v1-v0, v2-v0);
	}
};

template<typename T>
concept invokable_perpendicular_fn0 = requires(const T& t) {
	perpendicular_fn0{}(t);
};

}