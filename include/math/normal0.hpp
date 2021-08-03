#pragma once

//#include "perpendicular.hpp"
#include "vector.hpp"

namespace math::internal {

template<typename T>
concept has_normal_unqualified = requires(const T& t) {
	{ normal(t) } -> math::vector;
};

template<typename T>
concept has_normal_member = requires(const T& t) {
	{ t.normal() } -> math::vector;
};

struct normal_fn0 {
	template<has_normal_member T>
	constexpr auto operator () (const T& t) const {
		return t.normal();
	}

	template<has_normal_unqualified T>
	constexpr auto operator () (const T& t) const {
		return normal(t);
	}
};

template<typename T>
concept invokable_normal_fn0 = requires(const T& t) {
	normal_fn0{}(t);
};

}