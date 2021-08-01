#include "math/plane.hpp"
#include <glm/vec3.hpp>
#include <cassert>

int main() {
	using namespace math;
	using namespace glm;

	plane_by_normal_d p{ vec3{1,0,0}, 1.0F };
	static_assert(plane<plane_by_normal_d<vec3, float>>);

	vec3 n{1,0,0};
	assert(normal(p) == n);
	
	assert(d_for_normal(p) == 1.0F);

	plane_by_perpendicular_d p0{ vec3{1,0,0}, 1.0F };
	static_assert(plane<plane_by_perpendicular_d<vec3, float>>);
	static_assert(has_normal<plane_by_perpendicular_d<vec3, float>>);
	static_assert(has_d_for_normal<plane_by_perpendicular_d<vec3, float>>);
}