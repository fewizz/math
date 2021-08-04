#pragma once

#include <cinttypes>
#include <tuple>
#include <type_traits>
#include <utility>

namespace math {

template<typename T, std::size_t Index>
concept has_get_for_index = requires(const T& t) {
	get<Index>(t);
};

template<typename T, std::size_t... Index>
constexpr bool has_get_for_indexes(std::index_sequence<Index...>) {
	return (has_get_for_index<T, Index> && ...);
}

template<typename T>
concept has_tuple_size = requires {
	std::tuple_size<std::remove_cvref_t<T>>::value;
};

template<typename T, std::size_t Index>
concept has_tuple_element_for_index = requires {
	typename std::tuple_element<Index, std::remove_cvref_t<T>>::type;
};

template<typename T, typename... Ts, std::size_t... Index>
constexpr bool has_tuple_elements_same_as_for_indexes(std::index_sequence<Index...>) {
	return (has_tuple_element_for_index<Ts, Index> && ...);
}

template<typename T>
concept std_tuple_like =
	has_tuple_size<T>
	&& has_get_for_indexes<T>(
		std::make_index_sequence<std::tuple_size<T>::value>{}
	);

template<typename T, typename... Ts>
concept std_tuple_like_of =
	std_tuple_like<T>
	&& has_tuple_elements_same_as_for_indexes<T, Ts...>(
		std::make_index_sequence<std::tuple_size<T>::value>{}
	);

}