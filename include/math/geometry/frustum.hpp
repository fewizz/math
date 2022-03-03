#pragma once

#include "../matrix.hpp"

namespace math::geometry {
	
	template<typename Type>
	math::matrix<Type, 4, 4>
	frustum(
		Type l, Type r,
		Type b, Type t,
		Type n, Type f
	) {
		return {{
			{ 2 * n / (r - l),               0, (r + l) / (r - l),                   0 },
			{               0, 2 * n / (t - b), (t + b) / (t - b),                   0 },
			{               0,               0, (f + n) / (f - n), 2 * f * n / (f - n) },
			{               0,               0,                -1,                   0 }
		}};
	}

	template<typename Type>
	math::matrix<Type, 4, 4>
	perspective(Type fov, Type aspect, Type near, Type far) {
		Type half = __builtin_tan(fov / 2) * near;

		return frustum(-half, half, -half / aspect, half / aspect, near, far);
	}

}