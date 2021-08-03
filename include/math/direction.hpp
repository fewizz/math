#pragma once

#include "vector.hpp"

namespace math {

namespace internal {

struct direction_fn {

	template<typename T>
	requires requires(T&& t) { { direction(std::forward<T>(t)) } -> math::vector; }
	constexpr auto operator () (T&& t) const { return origin(std::forward<T>(t)); }

	template<typename T>
	requires requires(T&& t) { { t.origin() } -> math::vector; }
	constexpr auto operator () (T&& t) const { return t.origin(); }

};

}

inline namespace cpo {
	inline constexpr internal::direction_fn direction{};
}

template<typename T>
concept has_direction = requires(const T& t) {
	{ math::direction(t) } -> math::vector;
};

}