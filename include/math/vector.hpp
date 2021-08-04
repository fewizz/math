#pragma once

#include "tuple.hpp"

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
		length(t);
	}
;

/*template<math::vector A, math::vector B>
requires(math::size<A> == math::size<B>)
auto operator + (A a, B b) {
	math::internal::for_each_element([](auto& a, auto b) { a += b; }, a, b);
	return a;
}

template<math::vector A>
auto operator - (A a) {
	math::internal::for_each_element([](auto& a) { a = -a; }, a);
	return a;
}

template<math::vector A, math::vector B>
requires(math::size<A> == math::size<B>)
auto operator * (A a, B b) {
	math::internal::for_each_element([](auto& a, auto b) { a *= b; }, a, b);
	return a;
}

template<math::vector A>
auto operator * (A a, auto val) {
	math::internal::for_each_element([=](auto& a) { a *= val; }, a);
	return a;
}

template<math::vector A, math::vector B>
requires(math::size<A> == math::size<B>)
auto operator / (A a, B b) {
	math::internal::for_each_element([](auto& a, auto b) { a /= b; }, a, b);
	return a;
}

template<math::vector A>
auto operator / (A a, auto val) {
	math::internal::for_each_element([=](auto& a) { a /= val; }, a);
	return a;
}

namespace math {

template<math::vector A, math::vector B, std::size_t... Indexes>
requires(math::size<A> == math::size<B>)
auto dot(A a, B b) {
	if constexpr(sizeof...(Indexes) == math::size<A>) {
		auto m = a * b;
		return (get<Indexes>(m) + ...);
	}
	else return dot<A, B, Indexes..., sizeof...(Indexes)>(a, b);
}

auto length(math::vector auto v) {
	return std::sqrt(dot(v, v));
}

template<math::vector V>
using length_type = decltype(math::length(std::declval<V>()));

auto normalized(math::vector auto v) {
	return v / length(v);
}

template<math::vector V, math::vector V0, math::vector V1>
requires(math::size<V> == 3 && math::size<V0> == 3 && math::size<V1> == 3)
auto cross(V0 v0, V1 v1) {
	return V {
		math::get<1>(v0) * math::get<2>(v1) - math::get<2>(v0) * math::get<1>(v1),
		math::get<2>(v0) * math::get<0>(v1) - math::get<0>(v0) * math::get<2>(v1),
		math::get<0>(v0) * math::get<1>(v1) - math::get<1>(v0) * math::get<0>(v1)
	};
}

template<math::vector V>
requires(math::size<V> == 3)
V cross(V v0, V v1) {
	return cross<V, V, V>(v0, v1);
}*/

}