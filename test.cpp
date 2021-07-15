#if 0
$CXX --config ./compile_flags.txt -o /tmp/test test.cpp
/tmp/test
exit
#endif

#include <glm/ext/vector_float2.hpp>
#include <vector>
#include <string>
#include <assert.h>

#include "include/unified_math/vec.hpp"
#include "glm/vec2.hpp"
#include "include/unified_math/to.hpp"

using namespace uni;
using namespace std;

int main() {
	static_assert(has_get_for_index<std::pair<int, int>, 0>);
	static_assert(!vec<int, 2, int>);
	static_assert(vec<pair<int, int>, 2, int>);
	static_assert(!vec<std::pair<int, int>, 2, float>);
	static_assert(vec<glm::vec2, 2, float>);
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