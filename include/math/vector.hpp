#pragma once

#include <cinttypes>
#include <concepts>
#include <tuple>

namespace math {

namespace internal {
	template<typename T, std::size_t Index>
	concept has_get_for_index = requires(const T& t) {
		get<Index>(t);
	};

	template<typename T, std::size_t Index>
	constexpr bool has_get_for_indexes_up_to() {
		if constexpr(has_get_for_index<T, Index>) {
			if constexpr(Index == 0) return true;
			else return has_get_for_indexes_up_to<T, Index - 1>;
		}
		return false;
	}

	template<typename T>
	concept has_tuple_size = requires {
		{ std::tuple_size<T>::value } -> std::integral;
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
		&& has_get_for_indexes_up_to<T, std::tuple_size<T>::value - 1>();

	template<typename T, typename... Ts>
	concept std_tuple_like_of =
		std_tuple_like<T>
		&& has_tuple_elements_for_indexes_up_to_same_as<T, std::tuple_size<T>::value - 1, Ts...>();

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
		typename T::value_type;
	};

	template<typename T>
	concept glm_vector_like =
		has_subscription_operator<T>
		&& has_length_member<T>
		&& has_value_type<T>;

	template<typename T, typename... Ts>
	concept glm_vector_like_of =
		glm_vector_like<T>
		&& std::is_same_v<typename T::value_type, Ts...>;

	template<std_tuple_like T>
	constexpr auto size(const T& v) {
		return tuple_size<T>();
	}

	constexpr auto size(const glm_vector_like auto& v) {
		return v.length();
	}

	template<typename T>
	constexpr auto size_of_default_initialized() {
		return size(T{});
	}

}

template<typename T, typename... Ts>
concept vector =
	(
		internal::std_tuple_like_of<T, Ts...>
		||
		internal::glm_vector_like_of<T, Ts...>
	)
	&&
	std::default_initializable<T>
	&&
	std::constructible_from<T, Ts...>
;

template<vector V>
auto size(const V& v) {
	if constexpr(internal::std_tuple_like<V>) {
		return tuple_size<V>();
	}
	else {
		return v.length();
	}
}

template<vector V, std::size_t Index>
auto get(const V& v) {
	if constexpr(internal::std_tuple_like<V>) {
		return get<Index>(v);
	}
	else {
		return v[Index];
	}
}

auto operator + (const vector auto& a, const vector auto& b) {
	
}

}