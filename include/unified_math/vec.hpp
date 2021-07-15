#pragma once

//#if __has_include("glm/detail/qualifier.hpp")
#include "glm.hpp"
//#endif

#include <cstddef>
#include <type_traits>
#include <utility>
#include <concepts>
#include <tuple>
#include <limits>

namespace uni {

template<typename T, std::size_t Index>
concept has_get_for_index = requires(T& t) {
	get<Index>(t);
};

template<typename T>
inline constexpr std::size_t size = std::tuple_size_v<T>;

template<typename T>
concept has_size = requires {
	typename std::tuple_size<T>::type;
};

template<typename T, std::size_t Index>
using get_type = decltype(get<Index>(std::declval<T&>()));

template<typename T, std::size_t Index>
using get_type_decayed = std::decay_t<decltype(get<Index>(std::declval<T&>()))>;

namespace internal {
	template<typename T, std::size_t Index = 1>
	requires(has_get_for_index<T, 0>)
	consteval bool has_same_types() {
		if constexpr(Index < size<T>) {
			if constexpr(std::is_same_v<get_type<T, 0>, get_type<T, Index>>) {
				return has_same_types<T, Index + 1>();
			}
		}
		else return true;

		return false;
	}
};

template<typename T>
concept any_vec =
	has_size<T>
	&& size<T> > 0
	&& sizeof(T) == size<T> * sizeof(get_type_decayed<T, 0>)
	&& internal::has_same_types<T>();

template<typename T, std::size_t S>
concept vec_of_size =
	any_vec<T>
	&& size<T> == S;

template<typename T, typename E>
concept vec_of_type =
	any_vec<T>
	&& std::is_same_v<get_type_decayed<T, 0>, E>;

template<typename T, std::size_t S, class E>
concept vec = vec_of_size<T, S> && vec_of_type<T, E>;

}