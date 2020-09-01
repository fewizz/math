#pragma once

namespace uni {

template<class T>
struct vec_traits;

template<unsigned D, class E>
struct vec_traits_specialiser {
    static constexpr unsigned dimension = D;
    using element_type = E;
};

template<class T>
concept has_vec_traits = requires {
    vec_traits<T>::dimension;
    typename vec_traits<T>::element_type;
};

}