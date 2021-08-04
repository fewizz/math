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
		using type = std::tuple_element<Index, T>;

		constexpr decltype(auto) get(T&& t) const {
			return std::get<Index>(std::forward<T>(t));
		}
	};

	template<glm_vector_like T, std::size_t Index>
	struct element<T, Index> {
		using type = typename std::remove_reference_t<T>::value_type;

		constexpr decltype(auto) get(T&& t) const {
			return t[Index];
		}
	};
}

template<tuple T>
inline constexpr std::size_t size = internal::size<T>();

template<tuple T, std::size_t Index>
using element_type = typename internal::element<T, Index>::type;

template<tuple T, std::size_t Index>
constexpr decltype(auto) element(T&& t) {
	return internal::element<T, Index>::get(std::forward<T>(t));
}

namespace internal {
	template<tuple From, tuple To, std::size_t... Index>
	requires(math::size<From> == math::size<To>)
	constexpr To to(const From& from, std::index_sequence<Index...>) {
		return { (math::element<Index>(from) , ...) };
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

template<tuple From, tuple To>
constexpr To to(const From& from) {
	return internal::to(from, std::make_index_sequence<math::size<To>>());
}

template<tuple T>
using common_element_type = typename internal::common_element<T>::type;


}