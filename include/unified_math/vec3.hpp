#pragma once

#include "vec.hpp"

namespace uni {

template<class V, class T> concept vec3 = vec<V, 3, T>;
template<class V> concept vec3f = vec<V, 3, float>;
template<class V> concept vec3d = vec<V, 3, double>;
template<class V> concept vec3ui = vec<V, 3, unsigned>;
template<class V> concept vec3i = vec<V, 3, int>;

}