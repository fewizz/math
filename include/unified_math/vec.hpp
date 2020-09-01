#pragma once

#include <bits/c++config.h>
#if __has_include("glm/detail/qualifier.hpp")
    #include "glm.hpp"
#endif

#include <cstddef>
#include <type_traits>
#include <utility>
#include <concepts>
#include <tuple>
//#include "vec_traits.hpp"
#include <experimental/type_traits>

namespace uni {

template<class V, std::size_t I, class T>
struct has_get {
    template<class V0>
    using get_t = decltype(std::get<I>( std::declval<V0>() ));

    static constexpr bool value = std::is_same_v<
        std::decay_t<std::experimental::detected_t<get_t, V>>,
        T
    >;
};

template<class V, std::size_t D, class T>
struct is_vec {
    template<unsigned D0, class...Unused>
    struct recursive_get_check {
        static constexpr bool value =
            has_get<V, D0, T>::value and recursive_get_check<D0-1>::value;
    };

    template<class...Unused>
    struct recursive_get_check<0, Unused...> {
        static constexpr bool value = has_get<V, 0, T>::value;
    };

    static constexpr bool value =
        (sizeof(V) == D*sizeof(T)) and recursive_get_check<D-1>::value;
};

template<class V, std::size_t D, class T>
static constexpr bool is_vec_v = is_vec<V, D, T>::value;

template<class V, std::size_t D, class T>
concept vec = is_vec_v<V, D, T>;

//template<unsigned D, class T>
//struct vec_t;

/*template<class Vec> requires has_vec_traits<std::remove_cvref_t<Vec>>
auto vec_from(Vec v) {
    return vec<vec_traits<Vec>::dimension, typename vec_traits<Vec>::element_type>{};
}

template<class V0, class V1, class... Vs>
struct they_are_same
: std::integral_constant<bool, std::is_same_v<V0, V1> && they_are_same<V1, Vs...>::value> {};

template<class V0, class V1>
struct they_are_same<V0, V1>
: std::integral_constant<bool, std::is_same_v<V0, V1>> {};

template<class V0, class V1, class... Vs>
constexpr bool they_are_same_v = they_are_same<V0, V1, Vs...>::value;

template<class E0, class E1, class... E> requires
std::is_arithmetic_v<E0> && they_are_same_v<E0, E1, E...>
auto vec_from(E0 e0, E1 e1, E... elements) {
    return vec<sizeof...(E)+2, E0>{elements...};
}*/

}