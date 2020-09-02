#pragma once

#include "vec.hpp"

namespace uni {

template<class V, class T> concept vec2 = vec<V, 2, T>;
template<class V> concept vec2f = vec<V, 2, float>;
template<class V> concept vec2d = vec<V, 2, double>;
template<class V> concept vec2ui = vec<V, 2, unsigned>;
template<class V> concept vec2i = vec<V, 2, int>;

using pair_f = std::pair<float, float>;
using pair_d = std::pair<double, double>;
using pair_ui = std::pair<unsigned, unsigned>;
using pair_i = std::pair<int, int>;

}