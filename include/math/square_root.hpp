#pragma once

namespace math {

	template<typename Type>
	Type square_root(Type val) {
		return __builtin_sqrt(val);
	}

}