#if 0
$CXX --config ./compile_flags.txt -g -o /tmp/test test.cpp
/tmp/test
exit
#endif

#include <vector>
#include <string>
#include <assert.h>

#include "math/vector.hpp"
#include <glm/vec2.hpp>

int main() {
	using namespace std;

	//static_assert(has_get_for_index<std::pair<int, int>, 0>);
	static_assert(!math::vector<int>);
	static_assert(math::vector_of<pair<int, int>, int, int>);
	static_assert(!math::vector_of<std::pair<int, int>, float, float>);
	static_assert(math::vector_of<glm::vec2, float, float>);
	static_assert(math::vector_of<std::tuple<double, double, double, double>, double, double, double, double>);
	//static_assert(any_vec<tuple<char, char>>);
	//static_assert(any_vec<pair<float, float>>);
	//static_assert(!any_vec<int>);
	//static_assert(!any_vec<tuple<int, unsigned, char>>);

	glm::vec2 v{1.0F, 12.0F};
	auto p = math::to<std::pair<float, float>>(v);
	static_assert(is_same_v<decltype(p), pair<float, float>>);
	assert(math::get<0>(v) == math::get<0>(p) && math::get<1>(v) == math::get<1>(p));

	std::pair<float, float> one_pair{1.0F, 1.0F};

	auto sum = v + one_pair;
	assert(sum.x == 2.0F && sum.y == 13.0F);

	std::pair<float, float> rotated{-1.0F, 1.0F};
	assert(math::dot(one_pair, rotated) == 0.0F);
}