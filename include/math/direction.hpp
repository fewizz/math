#pragma once

#include "vector.hpp"

namespace math {

namespace internal {

struct direction_fn {

	template<typename T>
	requires requires(const T& t) { { direction(t) } -> math::vector; }
	constexpr auto operator () (const T& t) const { return direction(t); }

	template<typename T>
	requires requires(T& t) { { t.direction() } -> math::vector; }
	constexpr auto operator () (const T& t) const { return t.direction(); }

};

}

inline namespace cpo {
	inline constexpr internal::direction_fn direction{};
}

template<typename T>
concept has_direction = requires(const T& t) {
	{ internal::direction_fn{}(t) } -> math::vector;
};

}