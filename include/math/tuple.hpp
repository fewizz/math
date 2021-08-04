#pragma once

#include "std_tuple_like.hpp"
#include "glm_vector_like.hpp"

namespace math {

template<typename T>
concept tuple = math::std_tuple_like<T> || math::glm_vector_like<T>;

template<tuple T>



}