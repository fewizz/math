#include <glm/ext/vector_float2.hpp>
#include <vector>
#include <string>

#include "include/unified_math/vec2.hpp"
#include "glm/vec2.hpp"

using namespace uni;
using namespace std;

void exec(vector<string> args) {
    static_assert(is_vec_v<std::pair<int, int>, 2, int>);
    static_assert(is_vec_v<glm::vec2, 2, float>);
    static_assert(is_vec_v<std::tuple<double, double, double, double>, 4, double>);
    static_assert(is_any_vec<std::tuple<char, char>>::value);
}