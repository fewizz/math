#include "math/matrix.hpp"

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
	math::matrix<double, 3, 3> {{
		{ 2.0,-3.0, 1.0 },
		{ 2.0, 0.0,-1.0 },
		{ 1.0, 4.0, 5.0 }
	}}.minor(2, 1) == -4
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

static_assert(
	math::matrix<double, 2, 2> {{
		{ 1.0,-1.0 },
		{ 0.0, 2.0 }
	}}.inversed() == 
		math::matrix<double, 2, 2> {{
		{ 1.0, 0.5 },
		{ 0.0, 0.5 }
	}}
);

static_assert(
	math::matrix<double, 2, 3> {{
		{ 1, 2, 3 },
		{ 4, 5, 6 }
	}} * 
	math::matrix<double, 3, 2> {{
		{ 10, 11 },
		{ 20, 21 },
		{ 30, 31 }
	}} ==
	math::matrix<double, 2, 2> {{
		{ 140, 146 },
		{ 320, 335 }
	}}
);

static_assert(
	math::matrix<double, 3, 2> {{
		{ 0, 1 },
		{ 2, 4 },
		{ 1,-1 }
	}}.transposed() == 
	math::matrix<double, 2, 3> {{
		{ 0, 2, 1 },
		{ 1, 4,-1 }
	}}
);

int main() {}