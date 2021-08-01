#include "math/ray.hpp"
#include <glm/vec3.hpp>

int main() {
	using namespace math;
	using namespace glm;

	ray_by_point_and_direction r{ vec3{0,0,0}, vec3(1,0,0)};
	static_assert(math::ray<decltype(r)>);
}