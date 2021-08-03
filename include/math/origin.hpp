#pragma once

#include "point.hpp"

namespace math {

namespace internal {

struct origin_fn {

	template<typename T>
	requires requires(T&& t) { { origin(std::forward<T>(t)) } -> math::point; }
	constexpr auto operator () (T&& t) const { return origin(std::forward<T>(t)); }

	template<typename T>
	requires requires(T&& t) { { t.origin() } -> math::point; }
	constexpr auto operator () (T&& t) const { return t.origin(); }

};

}

inline namespace cpo {
	inline constexpr internal::origin_fn origin{};
}

template<typename T>
concept has_origin = requires(const T& t) {
	{ math::origin(t) } -> math::point;
};

}