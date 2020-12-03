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

namespace internal {
    template<std::size_t I>
    struct for_index {
        template<class T0>
        using get_t = decltype(std::get<I>( std::declval<T0>() ));
    };
}

template<class T, std::size_t I>
static constexpr bool has_get_for_index() {
    return std::experimental::is_detected_v<internal::for_index<I>::template get_t, T>;
}

template<class T, std::size_t... Is>
static constexpr bool has_gets_for_indicies() {
    return (has_get_for_index<T, Is>() && ...);
}

template<class T, std::size_t... Indexes>
static constexpr bool has_gets_for_indicies(std::index_sequence<Indexes...>) {
    return has_gets_for_indicies<T, Indexes...>();
}

template<class T, std::size_t I>
static constexpr bool has_same_gets_for_indicies() {
    return has_get_for_index<T, I>();
}

template<class T, std::size_t I0, std::size_t I1, std::size_t... Is>
static constexpr bool has_same_gets_for_indicies() {
    if constexpr(has_get_for_index<T, I0>() && has_get_for_index<T, I1>()) {
        return std::is_same_v<
            invoke_result_of_get_t<T, I0>,
            invoke_result_of_get_t<T, I1>
        > and has_same_gets_for_indicies<T, I1, Is...>();
    }
    return false;
}

template<class T, std::size_t... Indexes>
static constexpr bool has_same_gets_for_indicies(std::index_sequence<Indexes...>) {
    return has_same_gets_for_indicies<T, Indexes...>();
}

template<class T, std::size_t S>
static constexpr bool has_gets_for_size() {
    return has_gets_for_indicies<T>(std::make_index_sequence<S>());
}

template<class T, std::size_t S>
static constexpr bool has_same_gets_for_size() {
    return has_same_gets_for_indicies<T>(std::make_index_sequence<S>());
}

template<class T, class N, std::size_t S, class...Args>
static constexpr bool is_constructible_from_n_same_args() {
    if constexpr(sizeof...(Args) != S)
        return is_constructible_from_n_same_args<T, N, S, Args..., N>();
    return std::is_constructible_v<T, Args...>;
}

template<class T, std::size_t S, class E>
static constexpr bool is_vec() {
    if constexpr(has_same_gets_for_size<T, S>()) {
        using decayed_get_0 = std::decay_t<decltype(std::get<0>(std::declval<T>()))>;

        return
            std::is_same_v<decayed_get_0, E>
            and
            is_constructible_from_n_same_args<T, E, S>()
            and
            sizeof(T) == S*sizeof(E)
            and
            std::is_arithmetic_v<E>;
    }
    return false;
}

template<class T, std::size_t S, class E>
static constexpr bool is_vec_v = is_vec<T, S, E>();

template<class T>
static constexpr bool is_any_vec() {
    if constexpr(has_get_for_index<T, 0>()) {
        using decayed_get_0 = std::decay_t<decltype(std::get<0>(std::declval<T>()))>;

        return is_vec<T, sizeof(T)/sizeof(decayed_get_0), decayed_get_0>();
    }

    return false;
}

template<class T>
static constexpr bool is_any_vec_v = is_any_vec<T>();

template<class T, std::size_t S, class E>
concept vec = is_vec_v<T, S, E>;

template<class T>
concept any_vec = is_any_vec_v<T>;

}