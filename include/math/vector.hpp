#pragma once

#include "tuple.hpp"
#include <cmath>

namespace math {

namespace internal {
	template<typename T>
	struct common_element_or_void {
		using type = void;
	};

	template<tuple T>
	struct common_element_or_void<T> {
		using type = math::common_element_type<T>;
	};
}

template<typename T, typename N = typename internal::common_element_or_void<T>::type>
concept vector =
	math::tuple<T>
	&& requires(const T& t, N n) {
		t + t;
		t - t;
		t * n;
		t / n;

		dot(t, t);
	}
;

auto length(math::vector auto v) {
	return std::sqrt(dot(v, v));
}

auto normalize(math::vector auto v) {
	return v / length(v);
}

}