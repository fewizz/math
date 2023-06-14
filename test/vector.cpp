#include <math/vector.hpp>

consteval math::vector<double, 4> f0() {
	return { 0.0, 1.0, 2.0, 3.0 };
}

consteval bool f1() {
	auto v = f0();
	v = f0();

	auto [e0, e1, e2, e3] = f0();
	return e0 == 0.0 && e1 == 1.0 && e2 == 2.0 && e3 == 3.0;
}

static_assert(f1());

int main() {
	[[maybe_unused]] math::vector<float, 2> v{ 0.0F, 0.0F};
}