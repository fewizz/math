#pragma once

#include <concepts>

namespace math {

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

}