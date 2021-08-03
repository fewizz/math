#pragma once

#include "point.hpp"

namespace math {

namespace internal {

struct origin_fn {

	template<typename T>
	requires requires(const T& t) { { origin(t) } -> math::point; }
	constexpr auto operator () (const T& t) const { return origin(t); }

	template<typename T>
	requires requires(const T& t) { { t.origin() } -> math::point; }
	constexpr auto operator () (const T& t) const { return t.origin(); }

};

}

inline namespace cpo {
	inline constexpr internal::origin_fn origin{};
}

template<typename T>
concept has_origin = requires(const T& t) {
	{ internal::origin_fn{}(t) } -> math::point;
};

}