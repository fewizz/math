#pragma once

#include "point.hpp"
#include "segment.hpp"

namespace math {

namespace internal {

struct origin_fn {

	template<typename T>
	requires requires(const T& t) { { origin(t) } -> math::point; }
	constexpr auto operator () (const T& t) const { return origin(t); }

	template<typename T>
	requires requires(const T& t) { { t.origin() } -> math::point; }
	constexpr auto operator () (const T& t) const { return t.origin(); }

	template<math::segment T>
	constexpr auto operator () (const T& t) const { return math::vertex<0>(t); }
};

}

inline namespace cpo {
	inline constexpr internal::origin_fn origin{};
}

template<typename T>
concept has_origin = requires(const T& t) {
	{ internal::origin_fn{}(t) } -> math::point;
};

template<has_origin T>
using origin_type = decltype(origin(std::declval<T>()));

}