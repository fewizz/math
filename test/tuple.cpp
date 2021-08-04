#include "math/tuple.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

int main() {
	using namespace std;
	
	static_assert(!math::tuple<int>);
	static_assert(math::tuple_of<pair<int, int>, int, int>);
	static_assert(!math::tuple_of<std::pair<int, int>, float, float>);
	static_assert(math::tuple_of<glm::vec2, float, float>);
	static_assert(math::tuple_of<glm::vec3, float, float, float>);
	static_assert(math::tuple_of<std::tuple<double, double, double, double>, double, double, double, double>);

}