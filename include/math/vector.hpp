#pragma once

#include <cinttypes>
#include <concepts>
#include <cstddef>
#include <iterator>
#include <tuple>
#include <type_traits>
#include <cmath>

namespace math {

namespace internal {

	template<typename T, std::size_t Index>
	struct element;

	template<std_tuple_like T, std::size_t Index>
	struct element<T, Index> { using type = typename std::tuple_element<Index, T>::type; };

	template<glm_vector_like T, std::size_t Index>
	struct element<T, Index> { using type = typename T::value_type; };

	template<std_tuple_like T>
	constexpr auto size() {
		return std::tuple_size<std::remove_reference_t<T>>::value;
	}

	template<glm_vector_like T>
	constexpr auto size() {
		return std::remove_reference_t<T>{}.length();
	}

	template<typename T, typename... Ts>
	constexpr bool constructible_from_elements() {
		if constexpr(size<T>() != sizeof...(Ts)) {
			return constructible_from_elements<T, Ts..., typename element<T, sizeof...(Ts)>::type>();
		}
		else {
			return std::constructible_from<T, Ts...>;
		}
	}

}

template<typename T>
concept vector =
	(
		internal::std_tuple_like<T>
		||
		internal::glm_vector_like<T>
	)
	&&
	std::default_initializable<std::remove_reference_t<T>>
	&&
	internal::constructible_from_elements<std::remove_reference_t<T>>()
;

template<typename T, typename... Ts>
concept vector_of =
	vector<T>
	&&
	(
		internal::std_tuple_like_of<T, Ts...>
		||
		internal::glm_vector_like_of<T, Ts...>
	)
;

template<math::vector V>
inline constexpr std::size_t size = internal::size<V>();

template<math::vector V, std::size_t Index>
using element_type = typename internal::element<V, Index>::type;

template<std::size_t Index, math::vector V>
decltype(auto) get(V&& v) {
	if constexpr(internal::std_tuple_like<V>) {
		return std::get<Index>(v);
	}
	else {
		return v[Index];
	}
}

namespace internal {
	template<math::vector To, math::vector From, typename...Ts>
	To to(From from, Ts... values) {
		if constexpr(sizeof...(Ts) == math::size<From>) {
			return { values... };
		}
		else {
			return to<To>(from, values..., get<sizeof...(Ts)>(from));
		}
	}

}

template<math::vector To>
To to(math::vector auto from) {
	return internal::to<To>(from);
}

namespace internal {
	template<math::vector V, typename F, std::size_t... Indexes>
	void for_each_element(F&& f, V&& v) {
		if constexpr(sizeof...(Indexes) == math::size<V>)
			(f(get<Indexes>(v)) , ...);
		else
			return for_each_element<V, F, Indexes..., sizeof...(Indexes)>(std::forward<F>(f), std::forward<V>(v));
	}

	template<math::vector A, math::vector B, typename F, std::size_t... Indexes>
	void for_each_element(F&& f, A&& a, B&& b) {
		if constexpr(sizeof...(Indexes) == math::size<A>)
			(f(get<Indexes>(a), get<Indexes>(b)) , ...);
		else
			return for_each_element<A, B, F, Indexes..., sizeof...(Indexes)>(std::forward<F>(f), std::forward<A>(a), std::forward<B>(b));
	}
	
}

}

template<math::vector A, math::vector B>
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
}

}