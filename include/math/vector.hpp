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
	// std tuple-like
	template<typename T, std::size_t Index>
	concept has_get_for_index = requires(const T& t) {
		get<Index>(t);
	};

	template<typename T, std::size_t Index>
	constexpr bool has_get_for_indexes_up_to() {
		if constexpr(has_get_for_index<T, Index>) {
			if constexpr(Index == 0) return true;
			else return has_get_for_indexes_up_to<T, Index - 1>();
		}
		return false;
	}

	template<typename T>
	concept has_tuple_size = requires {
		std::tuple_size<std::remove_reference_t<T>>::value;
	};

	template<typename T, std::size_t Index>
	concept has_tuple_element_for_index = requires {
		typename std::tuple_element<Index, T>::type;
	};

	template<typename T, std::size_t Index, typename T0, typename... Ts>
	constexpr bool has_tuple_elements_for_indexes_up_to_same_as() {
		if constexpr(has_tuple_element_for_index<T, Index>) {
			if constexpr(std::is_same_v<T0, typename std::tuple_element<Index, T>::type>) {
				if constexpr(Index != 0)
					return has_tuple_elements_for_indexes_up_to_same_as<T, Index - 1, Ts...>();
				else return true;
			}
		}
		return false;
	}

	template<typename T>
	concept std_tuple_like =
		has_tuple_size<T>
		&& has_get_for_indexes_up_to<T, std::tuple_size<std::remove_reference_t<T>>::value - 1>();

	template<typename T, typename... Ts>
	concept std_tuple_like_of =
		std_tuple_like<T>
		&& has_tuple_elements_for_indexes_up_to_same_as<T, std::tuple_size<T>::value - 1, Ts...>();


	// glm vec-like
	template<typename T>
	concept has_subscription_operator = requires(const T& t) {
		t[0];
	};

	template<typename T>
	concept has_length_member = requires(const T& t) {
		{ t.length() } -> std::integral;
	};

	template<typename T>
	concept has_value_type = requires {
		typename std::remove_reference_t<T>::value_type;
	};

	template<typename T>
	concept glm_vector_like =
		has_subscription_operator<T>
		&& has_length_member<T>
		&& has_value_type<T>;

	template<typename T, typename... Ts>
	concept glm_vector_like_of =
		glm_vector_like<T>
		&& (std::is_same_v<typename T::value_type, Ts> && ...);
	//

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
using element = typename internal::element<V, Index>::type;

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
	void for_each_element(V&& v, F&& f) {
		if constexpr(sizeof...(Indexes) == math::size<V>)
			(f(get<Indexes>(v)) , ...);
		else
			return for_each_element<V, F, Indexes..., sizeof...(Indexes)>(std::forward<V>(v), std::forward<F>(f));
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
	std::sqrt(dot(v, v));
}

auto normalized(math::vector auto v) {
	return v / length(v);
}

}