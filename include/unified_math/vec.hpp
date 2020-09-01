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
struct possible_vec {
    struct internal {
        template<class V0>
        using size_t = std::tuple_size<V0>;
    };
    using size_t = std::experimental::detected_t<internal::template size_t, T>;

    struct has_size : std::integral_constant<
        bool,
        not std::is_same_v<std::experimental::nonesuch, size_t>
    >{};

    static constexpr bool has_size_v = has_size::value;

    template<class...>
    struct with_size {
        static_assert(has_size_v, "this type doesn't has std::tuple_size specialisation");

        struct size : std::integral_constant<std::size_t, std::tuple_size_v<T>> {};
        static constexpr std::size_t size_v = size::value;

        struct internal {
            template<std::size_t I>
            struct index {
                static_assert(I<size_v, "index out of bounds");
                template<class V0>
                using get_t = decltype(std::get<I>( std::declval<V0>() ));
            };
        };

        template<std::size_t I>
        using get_t = std::experimental::detected_t<internal::template index<I>:: template get_t, T>;

        template<std::size_t I>
        using decayed_get_t = std::decay_t<get_t<I>>;

        template<std::size_t I>
        struct has_get : std::integral_constant<
            bool,
            not std::is_same_v<std::experimental::nonesuch, get_t<I>>
        >{};

        template<std::size_t I>
        static constexpr bool has_get_v = has_get<I>::value;

        template<std::size_t begin=0, class...>
        struct has_gets : std::integral_constant<
            bool,
            has_get_v<begin> and has_gets<begin+1>::value
        >{};

        template<class...Unused>
        struct has_gets<size_v - 1, Unused...> : std::integral_constant< bool, has_get_v<size_v - 1> >{};

        template<class... Unused>
        static constexpr bool has_gets_v = has_gets<0, Unused...>::value;

        template<class... Unused>
        struct with_gets {
            static_assert(has_gets_v<>, "this type doesn't has std::get specialisations for every index");

            template<std::size_t begin=0, class...>
            struct has_same_decayed_gets : std::integral_constant<
                bool,
                std::is_same_v<decayed_get_t<0>, decayed_get_t<begin>>
                 and has_same_decayed_gets<begin+1>::value
            >{};

            template<class...Unused0>
            struct has_same_decayed_gets<size_v - 1, Unused0...>
            : std::integral_constant< bool, std::is_same_v<get_t<0>, get_t<size_v - 1>> >{};

            static constexpr bool has_same_decayed_gets_v = has_same_decayed_gets<>::value;         
        };

        template<class...>
        struct with_same_gets {
            static_assert(with_gets<>::has_same_decayed_gets_v, "std::get specialisations don't have same RT");

            using get_t = get_t<0>;
            using decayed_get_t = decayed_get_t<0>;

            template<class T0>
            struct decayed_get_t_same_as
            : std::integral_constant<bool, std::is_same_v<T0, decayed_get_t>>{};
        };
    };

    template<std::size_t N, bool=has_size_v>
    struct has_size_of : std::integral_constant<bool, false>{};

    template<std::size_t N>
    struct has_size_of<N, true> : std::integral_constant<bool, with_size<>::size_v == N>{};

    struct has_size_and_same_decayed_gets {
        template<bool=has_size_v, class...>
        struct a : std::integral_constant<bool, false>{};
        template<class... Unused>
        struct a<true, Unused...>
        : std::integral_constant<bool, with_size<>::template has_gets_v<> >{};

        template<bool=a<>::value, class...>
        struct b : std::integral_constant<bool, false>{};
        template<class... Unused>
        struct b<true, Unused...>
        : std::integral_constant<
            bool,
            with_size<>::template with_gets<>::template has_same_decayed_gets<>::value
        >{};

        static constexpr bool value = b<>::value;
    };

    static constexpr bool has_size_and_same_decayed_gets_v =
        has_size_and_same_decayed_gets::value;
};


template<class V, std::size_t N, class T>
struct is_vec {
    using v = possible_vec<V>;

    template<
        bool=v::has_size_and_same_decayed_gets_v,
        class...
    >
    struct a : std::integral_constant<bool, false>{};
    template<class... Unused>
    struct a<true, Unused...>
    : std::integral_constant<
        bool,
        v::template with_size<>::size_v == N
        and v::template with_size<>::template with_same_gets<>::template decayed_get_t_same_as<T>::value
    >{};

    static constexpr bool value =
        a<>::value and
        sizeof(V) ==
        v::template with_size<>::size_v *
        sizeof(typename v::template with_size<>::decayed_get_t<0>);
};

template<class V, std::size_t D, class T>
static constexpr bool is_vec_v = is_vec<V, D, T>::value;

template<class V, std::size_t D, class T>
concept vec = is_vec_v<V, D, T>;

template<class V>
struct is_any_vec {
    using v = possible_vec<V>;

    template<
        bool=v::has_size_and_same_decayed_gets_v,
        class...
    >
    struct a : std::integral_constant<bool, false>{};
    template<class... Unused>
    struct a<true, Unused...>
    : std::integral_constant<
        bool,
        sizeof(V) ==
        v::template with_size<>::size_v *
        sizeof(typename v::template with_size<>::decayed_get_t<0>)
    >{};

    static constexpr bool value = a<>::value;
};

}