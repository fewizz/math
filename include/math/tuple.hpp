#pragma once

#include "std_tuple_like.hpp"
#include "glm_vector_like.hpp"
#include <type_traits>
#include <utility>

namespace math {

template<typename T>
concept tuple = math::std_tuple_like<T> || math::glm_vector_like<T>;

template<typename T, typename... Ts>
concept tuple_of =
	tuple<T>
	&& (math::std_tuple_like_of<T, Ts...> || math::glm_vector_like_of<T, Ts...>)
;

namespace internal {

	template<std_tuple_like T>
	constexpr std::size_t size() {
		return std::tuple_size<std::remove_cvref_t<T>>::value;
	}

	template<glm_vector_like T>
	constexpr std::size_t size() {
		return T{}.length();
	}

	template<typename, std::size_t> struct element;

	template<std_tuple_like T, std::size_t Index>
	struct element<T, Index> {
		using type = typename std::tuple_element<Index, std::remove_cvref_t<T>>::type;

		static constexpr decltype(auto) get(T&& t) {
			return get<Index>(std::forward<T>(t));
		}
	};

	template<glm_vector_like T, std::size_t Index>
	struct element<T, Index> {
		using type = typename std::remove_reference_t<T>::value_type;

		static constexpr decltype(auto) get(T&& t) {
			return t[Index];
		}
	};
}

template<tuple T>
inline constexpr std::size_t size = internal::size<T>();

template<tuple T, std::size_t Index>
using element_type = typename internal::element<T, Index>::type;

template<std::size_t Index, tuple T>
constexpr decltype(auto) element(T&& t) {
	return internal::element<T, Index>::get(std::forward<T>(t));
}

namespace internal {
	template<tuple To, tuple From, std::size_t... Index>
	requires(math::size<From> == math::size<To>)
	constexpr To to(const From& from, std::index_sequence<Index...>) {
		return { (math::element<Index>(from))... };
	}

	template<tuple T, typename...Ts>
	struct common_element {
		using type = typename common_element<T, Ts..., math::element_type<T, sizeof...(Ts)>>::type;
	};

	template<tuple T, typename...Ts>
	requires(math::size<T> == sizeof...(Ts))
	struct common_element<T, Ts...> {
		using type = std::common_type_t<Ts...>;
	};
}

template<tuple To, tuple From>
constexpr To to(const From& from) {
	return internal::to<To, From>(from, std::make_index_sequence<math::size<To>>());
}

template<tuple T>
using common_element_type = typename internal::common_element<T>::type;

namespace internal {
	template<tuple T, typename F, std::size_t... Index>
	constexpr void for_each_element(T&& t, F&& f, std::index_sequence<Index...>) {
		(f(math::element<Index>(t)) , ...);
	}

	template<tuple T0, tuple T1, typename F, std::size_t... Index>
	constexpr void for_each_element(T0&& t0, T1&& t1, F&& f, std::index_sequence<Index...>) {
		(f(math::element<Index>(t0), math::element<Index>(t1)) , ...);
	}
}

template<tuple T, typename F>
constexpr void for_each_element(T&& t, F&& f) {
	internal::for_each_element<T, F>(
		std::forward<T>(t),
		std::forward<F>(f),
		std::make_index_sequence<math::size<T>>()
	);
}

template<tuple T0, tuple T1, typename F>
requires(math::size<T0> == math::size<T1>)
constexpr void for_each_element(T0&& t0, T1&& t1, F&& f) {
	internal::for_each_element<T0, T1, F>(
		std::forward<T0>(t0),
		std::forward<T1>(t1),
		std::forward<F>(f),
		std::make_index_sequence<math::size<T0>>()
	);
}

}