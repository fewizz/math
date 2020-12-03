#include <glm/ext/vector_float2.hpp>
#include <vector>
#include <string>

#include "include/unified_math/vec.hpp"
#include "glm/vec2.hpp"
#include "include/unified_math/convert.hpp"
#include <assert.h>

using namespace uni;
using namespace std;

int main() {
    static_assert(!is_vec_v<int, 2, int>);
    static_assert(is_vec_v<pair<int, int>, 2, int>);
    static_assert(!is_vec_v<std::pair<int, int>, 2, float>);
    static_assert(is_vec_v<glm::vec2, 2, float>);
    static_assert(is_vec_v<tuple<double, double, double, double>, 4, double>);
    static_assert(is_any_vec_v<tuple<char, char>>);
    static_assert(is_any_vec_v<pair<float, float>>);
    static_assert(!is_any_vec_v<int>);
    static_assert(!is_any_vec_v<tuple<int, unsigned, char>>);

    glm::vec2 v{1.0F, 12.0F};
    auto p = convert<std::pair<float, float>>(v);
    static_assert(is_same_v<decltype(p), pair<float, float>>);
    assert(get<0>(v) == 1.0F and get<1>(v) == 12.0F);
}