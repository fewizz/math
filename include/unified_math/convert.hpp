#pragma once

#include "vec_traits.hpp"

namespace uni {

template<any_vec To, any_vec From, class...Ts>
To convert(From from, Ts... ts) {
    if constexpr(sizeof...(Ts) != vec_traits<From>::dimension)
        return convert<To>(from, ts..., (typename vec_traits<From>::element_type) {} );
    else return To{ts...};

}

}