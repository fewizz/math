#pragma once

#include <integer.hpp>

namespace math {

	constexpr nuint factorial(nuint initial) {
		nuint result = initial;

		while(--initial > 1) {
			result *= initial;
		}

		return result;
	}

}