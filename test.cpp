#if 0
$CXX --config ./compile_flags.txt -o /tmp/test test.cpp
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
	static_assert(math::vector<pair<int, int>, int, int>);
	static_assert(!math::vector<std::pair<int, int>, float, float>);
	static_assert(math::vector<glm::vec2, float, float>);
	static_assert(vec<tuple<double, double, double, double>, 4, double>);
	static_assert(any_vec<tuple<char, char>>);
	static_assert(any_vec<pair<float, float>>);
	static_assert(!any_vec<int>);
	static_assert(!any_vec<tuple<int, unsigned, char>>);

	glm::vec2 v{1.0F, 12.0F};
	auto p = uni::to<std::pair<float, float>>(v);
	static_assert(is_same_v<decltype(p), pair<float, float>>);
	assert(get<0>(v) == get<0>(p) && get<1>(v) == get<1>(p));
}