#pragma once

#include "tuple.hpp"
#include <type_traits>
#include <utility>
#include <cmath>

namespace math {

template<typename T>
struct is_cartesian_vector : std::false_type {};

template<typename T>
concept cartesian_vector =
	math::tuple<T>
	&& is_cartesian_vector<T>::value;

template<glm_vector_like T>
struct is_cartesian_vector<T> : std::true_type {};

template<math::tuple T>
struct cartesian_vector_by {
	using tuple_type = std::remove_cvref_t<T>;
	tuple_type tuple;

	cartesian_vector_by(const cartesian_vector_by&) = default;
	cartesian_vector_by(cartesian_vector_by&) = default;
	cartesian_vector_by(cartesian_vector_by&&) = default;

	template<typename... Args>
	cartesian_vector_by(Args&&... args)
		: tuple{ std::forward<Args>(args)... }
	{}

	decltype(auto) x() const
	requires(math::size<tuple_type> >= 1) {
		return math::element<0>(tuple);
	}

	decltype(auto) y() const
	requires(math::size<tuple_type> >= 2) {
		return math::element<1>(tuple);
	}

	decltype(auto) z() const
	requires(math::size<tuple_type> >= 3) {
		return math::element<2>(tuple);
	}

	cartesian_vector_by operator + (const math::tuple auto& other) const {
		cartesian_vector_by result{ *this };
		math::for_each_element(result, other, [](auto& r, const auto& o) {
			r += o;
		});
		return result;
	}

	cartesian_vector_by operator - (const math::tuple auto& other) const {
		cartesian_vector_by result{ *this };
		math::for_each_element(result, other, [](auto& r, const auto& o) {
			r -= o;
		});
		return result;
	}

	cartesian_vector_by operator * (const auto& to) const {
		cartesian_vector_by result{ *this };
		math::for_each_element(result, [&](auto& r) {
			r *= to;
		});
		return result;
	}

	cartesian_vector_by operator / (const auto& to) const {
		cartesian_vector_by result{ *this };
		math::for_each_element(result, [&](auto& r) {
			r /= to;
		});
		return result;
	}
};

template<math::tuple T>
struct is_cartesian_vector<cartesian_vector_by<T>> : std::true_type {};

template<std::size_t Index, math::tuple T>
decltype(auto) get(math::cartesian_vector_by<T>& v) {
	return get<Index>(v.tuple);
}

template<std::size_t Index, math::tuple T>
decltype(auto) get(const math::cartesian_vector_by<T>& v) {
	return get<Index>(v.tuple);
}

namespace internal {
	template<cartesian_vector V0, cartesian_vector V1, std::size_t... Index>
	auto dot(V0 v0, V1 v1, std::index_sequence<Index...>) {
		return ((math::element<Index>(v0) * math::element<Index>(v1)) + ...);
	}
}

template<tuple V0, tuple V1>
requires(math::size<V0> == math::size<V1>)
auto dot(V0 v0, V1 v1) {
	return internal::dot(v0, v1, std::make_index_sequence<math::size<V0>>());
}

template<math::cartesian_vector V, math::cartesian_vector V0, math::cartesian_vector V1>
requires(math::size<V> == 3 && math::size<V0> == 3 && math::size<V1> == 3)
V cross(V0 v0, V1 v1) {
	return {
		math::element<1>(v0) * math::element<2>(v1) - math::element<2>(v0) * math::element<1>(v1),
		math::element<2>(v0) * math::element<0>(v1) - math::element<0>(v0) * math::element<2>(v1),
		math::element<0>(v0) * math::element<1>(v1) - math::element<1>(v0) * math::element<0>(v1)
	};
}

}

template<math::tuple T>
struct std::tuple_size<math::cartesian_vector_by<T>>
	: std::integral_constant<std::size_t, math::size<T>>
{};

template<std::size_t Index, math::tuple T>
struct std::tuple_element<Index, math::cartesian_vector_by<T>> {
	using type = math::element_type<T, Index>;
};