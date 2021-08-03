#pragma once

namespace math {

namespace internal {

struct radius_fn {
	template<typename T>
	requires requires(const T& t) { radius(t); }
	constexpr auto operator() (const T& t) const {
		return radius(t);
	}

	template<typename T>
	requires requires(const T& t) { t.radius(); }
	constexpr auto operator() (const T& t) const {
		return t.radius();
	}
};

}

inline namespace cpo {
	inline constexpr internal::radius_fn radius{};
}

template<typename T>
concept has_radius = requires(const T& t) {
	internal::radius_fn{}(t);
};

}