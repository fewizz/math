#pragma once

#include "vec.hpp"

namespace uni {

template<class V, class T> concept vec4 = vec<V, 4, T>;
template<class V> concept vec4f = vec<V, 4, float>;
template<class V> concept vec4d = vec<V, 4, double>;
template<class V> concept vec4ui = vec<V, 4, unsigned>;
template<class V> concept vec4i = vec<V, 4, int>;

}