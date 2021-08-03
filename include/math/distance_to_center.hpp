#pragma once

#include "vertex.hpp"
#include "normal.hpp"

namespace math {

namespace internal {

struct distance_to_center_fn {

	template<typename T>
	requires requires(const T& t) { distance_to_center(t); }
	constexpr auto operator () (const T& t) const {
		return distance_to_center(t);
	}

	template<typename T>
	requires requires(const T& t) { t.distance_to_center(); }
	constexpr auto operator () (const T& t) const {
		return t.distance_to_center();
	}

	template<typename T>
	requires(math::has_normal<T> && math::has_vertex<T, 0>)
	constexpr auto operator () (const T& t) const {
		return -math::dot(math::normal(t), math::vertex<0>(t));
	}
};

}

inline namespace cpo {
	inline constexpr internal::distance_to_center_fn distance_to_center{};
}

template<typename T>
concept has_distance_to_center = requires(const T& t) {
	internal::distance_to_center_fn{}(t);
};

}