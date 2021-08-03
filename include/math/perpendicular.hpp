#pragma once

#include "perpendicular0.hpp"
#include "normal0.hpp"

namespace math {

namespace internal {

struct perpendicular_fn {
	template<internal::invokable_perpendicular_fn0 T>
	constexpr auto operator () (const T& t) const {
		return internal::perpendicular_fn0{}(t);
	}

	template<internal::invokable_normal_fn0 T>
	constexpr auto operator () (const T& t) const {
		return internal::normal_fn0{}(t);
	}
};

}

inline namespace cpo {
	inline constexpr auto perpendicular = internal::perpendicular_fn{};
}

template<typename T>
concept has_perpendicular = requires(const T& t) {
	{ math::internal::perpendicular_fn{}(t) } -> math::vector;
};

}