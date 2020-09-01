#pragma once

#include "vec.hpp"
#include "vec_traits.hpp"
#include <type_traits>

namespace uni {

//template<class V, class T>
//struct is_vec2 : std::integral_constant<bool, is_vec<V, 2, T>::value>{};

//using is_vec2

template<class V, class T> concept vec2 = vec<V, 2, T>;
template<class V> concept vec2f = vec<V, 2, float>;
template<class V> concept vec2d = vec<V, 2, double>;
template<class V> concept vec2ui = vec<V, 2, unsigned>;
template<class V> concept vec2i = vec<V, 2, int>;

/*template<class T>
struct vec_t<2, T> {
    union {
        struct {  T x, y; };
        struct { T width, height; };
    };

    template<class R> vec_t(R r);

    vec_t(): x{0}, y{0} {}

    vec_t(std::pair<T, T> pair)
    : vec_t(pair.first, pair.second) {}

    vec_t(T first, T second)
    : x{first}, y{second} {}

    template<class R>
    operator R();

    operator std::pair<T, T>() { return {x, y}; }
};

using vec2f_t = vec_t<2, float>;
using vec2d_t = vec_t<2, double>;
using vec2ui_t = vec_t<2, unsigned>;
using vec2i_t = vec_t<2, int>;

template<> struct vec_traits<vec2f_t> : vec_traits_specialiser<2, float> {};
template<> struct vec_traits<vec2d_t> : vec_traits_specialiser<2, double> {};
template<> struct vec_traits<vec2ui_t> : vec_traits_specialiser<2, unsigned> {};
template<> struct vec_traits<vec2i_t> : vec_traits_specialiser<2, int> {};*/

}