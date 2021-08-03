#include "math/plane.hpp"
#include <glm/vec3.hpp>
#include <cassert>

int main() {
	using namespace glm;

	math::plane_by_normal_and_distance_to_center p{ vec3{1,0,0}, 1.0F };
	static_assert(math::has_normal<decltype(p)>);
	static_assert(math::plane<decltype(p)>);

	vec3 n{1,0,0};
	assert(math::normal(p) == n);
	
	assert(distance_to_center(p) == 1.0F);

	math::plane_by_perpendicular_and_distance_to_center p0{ vec3{1,0,0}, 1.0F };
	static_assert(math::has_normal<decltype(p0)>);
	static_assert(math::plane<decltype(p0)>);
	static_assert(math::has_normal<decltype(p0)>);
	static_assert(math::has_distance_to_center<decltype(p0)>);
}