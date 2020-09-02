#pragma once

#include <bits/c++config.h>
#include <utility>
#include "vec.hpp"

namespace uni {

template<class T, bool=is_any_vec_v<T> >
struct vec_traits;

template<class T>
struct vec_traits<T, true> {
    static constexpr std::size_t dimension = std::tuple_size_v<T>;
    using element_type = invoke_result_of_get_t<T, 0>;
};

}