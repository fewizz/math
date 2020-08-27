#pragma once

#include <utility>
#include <initializer_list>

namespace uni {

template<unsigned D, class T>
struct vec;

template<class T>
struct vec<2, T> {
    union {
    
    struct {
        T x, y;
    };

    struct {
        T width, height;
    };

    };

    template<class R>
    vec(R r);

    /*vec(std::initializer_list<T> ilist) {
        if(ilist.size() >= 1) x = *ilist.begin();
        if(ilist.size() >= 2) y = *(ilist.begin() + 1);
    }*/

    vec(std::pair<T, T> pair)
    : vec(pair.first, pair.second) {}

    vec(T first, T second)
    : x{first}, y{second} {}

    template<class R>
    operator R();

    operator std::pair<T, T>() { return {x, y}; }
};

using vec2f = vec<2, float>;
using vec2ui = vec<2, unsigned>;
using vec2i = vec<2, int>;

}