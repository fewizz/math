#pragma once

#include <glm/detail/qualifier.hpp>
#include "glm/vec2.hpp"
#include <tuple>

template<std::size_t I, glm::length_t L, typename T, glm::qualifier Q>
requires(I < L)
T& get(glm::vec<L, T, Q>& vec ) {
	return vec[I];
}

template<std::size_t I, glm::length_t L, typename T, glm::qualifier Q>
requires(I < L)
T get(glm::vec<L, T, Q>&& vec ) {
	return vec[I];
}

template<glm::length_t L, typename T, glm::qualifier Q>
struct std::tuple_size<glm::vec<L, T, Q>> : std::integral_constant<std::size_t, L> { };