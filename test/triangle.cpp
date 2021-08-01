#include "math/triangle.hpp"
#include <glm/vec3.hpp>
#include <cassert>

int main() {
	using namespace math;
	using namespace glm;

	triangle_by_points<vec3> t{ vec3{0,0,0}, vec3{1,0,0}, vec3{0,0,-1} };

	vec3 p0{0,0,0};
	assert(point_0(t) == p0);
	vec3 p1{1,0,0};
	assert(point_1(t) == p1);
	vec3 p2{0,0,-1};
	assert(point_2(t) == p2);

	vec3 n{0,1,0};
	assert(normal(t) == n);
}