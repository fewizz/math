#pragma once

#include "normal0.hpp"
#include "perpendicular0.hpp"

namespace math {

namespace internal {

struct normal_fn {

	template<internal::invokable_perpendicular_fn0 T>
	constexpr auto operator () (const T& t) const {
		return math::normalized(internal::perpendicular_fn0{}(t));
	}

	template<internal::invokable_normal_fn0 T>
	constexpr auto operator () (const T& t) const {
		return internal::normal_fn0{}(t);
	}
};

}

inline namespace cpo {
	inline constexpr internal::normal_fn normal{};
}

template<typename T>
concept has_normal = requires(const T& t) {
	{ internal::normal_fn{}(t) } -> math::vector;
};

auto turn_normal_opposite_to_direction(math::vector auto n, math::vector auto d) {
	return math::dot(n, d) > 0 ? -n : n;
}

}