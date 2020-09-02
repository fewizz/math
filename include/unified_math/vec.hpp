#pragma once

#include <bits/c++config.h>
#include <corecrt.h>
#if __has_include("glm/detail/qualifier.hpp")
    #include "glm.hpp"
#endif

#include <cstddef>
#include <type_traits>
#include <utility>
#include <concepts>
#include <tuple>
#include <experimental/type_traits>
#include <limits>

namespace uni {

template<class T>
static constexpr bool has_tuple_size_v = std::experimental::is_detected_v<std::tuple_size, T>;

template<class T, std::size_t I>
using invoke_result_of_get_t = decltype(std::get<I>( std::declval<T>() ));

template<class T, std::size_t I>
class has_get_for_index {
    template<class T0>
    using get_t = decltype(std::get<I>( std::declval<T0>() ));
public:
    static constexpr bool value = std::experimental::is_detected_v<get_t, T>;
};

template<class T, std::size_t I>
static constexpr bool has_get_for_index_v = has_get_for_index<T, I>::value;

template<class T, std::size_t I0, std::size_t... Is>
class has_gets_for_indicies {
    template<std::size_t _I0, std::size_t _I1, std::size_t... _Is>
    static constexpr bool v() {
        return has_get_for_index_v<T, _I0> and has_get_for_index_v<T, _I1>;
    }
    template<std::size_t _I0>
    static constexpr bool v() {
        return has_get_for_index_v<T, _I0>;
    }
public: 
    static constexpr bool value = v<I0, Is...>();
};

template<class T, std::size_t... Is>
static constexpr bool has_gets_for_indicies_v = has_gets_for_indicies<T, Is...>::value;

template<class T, std::size_t I0, std::size_t I1, std::size_t... Is>
class has_same_gets_for_indicies {
    template<std::size_t _I0, std::size_t _I1, std::size_t _I2, std::size_t... _Is>
    static constexpr bool v() {
        return v<_I0, _I1>() and v<_I1, _I2, _Is...>();
    }

    template<std::size_t _I0, std::size_t _I1>
    static constexpr bool v() {
        return std::is_same_v<
            invoke_result_of_get_t<T, _I0>,
            invoke_result_of_get_t<T, _I1>
        >;
    }
public: 
    static constexpr bool value = v<I0, I1, Is...>();
};

template<class T, std::size_t...Is>
static constexpr bool has_same_gets_for_indicies_v =
    has_same_gets_for_indicies<T, Is...>::value;

namespace internal {
    template<template<class, std::size_t...> class C, class T, std::size_t N>
    class check_range_for {
        template<std::size_t... Is>
        static constexpr bool v(std::index_sequence<Is...>) {
            return C<T, Is...>::value;
        }
    public:
        static constexpr bool value = v(std::make_index_sequence<N>());
    };
}

template<class T, std::size_t S>
static constexpr bool has_gets_for_size_v =
    internal::check_range_for<has_gets_for_indicies, T, S>::value;

template<class T, std::size_t S>
static constexpr bool has_same_gets_for_size_v =
    internal::check_range_for<has_same_gets_for_indicies, T, S>::value;

template<class T, std::size_t S, class E>
class is_vec {
    template<bool=has_tuple_size_v<T> and has_gets_for_size_v<T, S>,class...>
    struct a:std::integral_constant<bool,false>{};
    
    template<class...U> struct a<true,U...>
    :std::integral_constant<
        bool,
        has_same_gets_for_size_v<T, S> and
        std::is_same_v<std::decay_t<decltype(std::get<0>(std::declval<T>()))>, E>
    >{};

    template<class...R>
    static constexpr bool b() {
        if constexpr(sizeof...(R) != S) return b<E, R...>();
        else return std::is_constructible_v<T, R...>;
    }
public:
    static constexpr bool value =
        a<>::value and b<>()
        and sizeof(T) == S*sizeof(E)
        and std::is_arithmetic_v<E>;
};

template<class T, std::size_t S, class E>
static constexpr bool is_vec_v = is_vec<T, S, E>::value;

template<class T>
class is_any_vec {
    template<class T0>
    using decayed = std::decay_t<invoke_result_of_get_t<T0, 0>>;

    template<bool=has_get_for_index_v<T, 0>, class...>
    struct a : std::integral_constant<bool, false>{};

    template<class...U>
    struct a<true, U...> : std::integral_constant<
        bool,
        is_vec_v<T, sizeof(T)/sizeof(decayed<T>), decayed<T>>
    >{};
public:
    static constexpr bool value = a<>::value;
};

template<class T>
static constexpr bool is_any_vec_v = is_any_vec<T>::value;

template<class T, std::size_t S, class E>
concept vec = is_vec_v<T, S, E>;

template<class T>
concept any_vec = is_any_vec_v<T>;

}