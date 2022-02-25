#include "math/matrix.hpp"

int main() {
	static_assert(
		math::matrix<double, 2, 2> {{
			{ 1.0, 0.0 },
			{ 0.0, 1.0 }
		}}.determinant() == 1
	);

	static_assert(
		math::matrix<double, 2, 2> {{
			{ 1.0, -1.0 },
			{ 1.0, 10.0 }
		}}.determinant() == 11
	);

	static_assert(
		math::matrix<double, 3, 3> {{
			{ 1.0, 0.0, 0.0 },
			{ 0.0, 1.0, 0.0 },
			{ 0.0, 0.0, 1.0 }
		}}.determinant() == 1
	);

	static_assert(
		math::matrix<double, 3, 3> {{
			{ 2.0,-3.0, 1.0 },
			{ 2.0, 0.0,-1.0 },
			{ 1.0, 4.0, 5.0 }
		}}.determinant() == 49
	);

	static_assert(
		math::matrix<double, 5, 5> {{
			{ 1.0, 2.0, 3.0, 4.0, 1.0 },
			{ 0.0,-1.0, 2.0, 4.0, 2.0 },
			{ 0.0, 0.0, 4.0, 0.0, 0.0 },
			{-3.0,-6.0,-9.0, -12, 4.0 },
			{ 0.0, 0.0, 1.0, 1.0, 1.0 }
		}}.determinant() == 28
	);
}