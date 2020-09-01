#pragma once

#include <glm/detail/qualifier.hpp>
#include "glm/vec2.hpp"
#include <tuple>

namespace std {

template<std::size_t I, glm::length_t L, class T, glm::qualifier Q>
T get(glm::vec<L, T, Q>& vec ) {
    return vec[I];
}

template<std::size_t I, glm::length_t L, class T, glm::qualifier Q>
T get(glm::vec<L, T, Q>&& vec ) {
    return vec[I];
}

template<glm::size_t L, class T, glm::qualifier Q>
struct tuple_size<glm::vec<L, T, Q>> : std::integral_constant<std::size_t, L> { };

}