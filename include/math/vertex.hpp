#pragma once

#include "point.hpp"
#include <cinttypes>

namespace math {

namespace internal {

template<std::size_t Index>
struct vertex_fn {

	template<typename T>
	requires requires(const T& t) { { vertex<Index>(t) } -> math::point; }
	constexpr auto operator () (const T& t) const {
		return vertex(t);
	}

	template<typename T>
	requires requires(const T& t) { { t.template vertex<Index>() } -> math::point; }
	constexpr auto operator () (const T& t) const {
		return t.template vertex<Index>();
	}
};

}

inline namespace cpo {
	template<std::size_t Index>
	inline constexpr internal::vertex_fn<Index> vertex{};
}

template<typename T, std::size_t Index>
concept has_vertex = requires(const T& t) {
	internal::vertex_fn<Index>{}(t);
};

}