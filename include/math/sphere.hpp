#pragma once

namespace math {

template<typename T>
concept sphere = requires(const T& t) {
	origin(t);
	radius(t);
};



}