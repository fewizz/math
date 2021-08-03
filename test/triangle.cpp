#include "math/triangle.hpp"
#include "math/plane.hpp"
#include <glm/vec3.hpp>
#include <cassert>

int main() {
	//using namespace math;
	using namespace glm;

	math::triangle_by_points<vec3> t{ vec3{0,0,0}, vec3{1,0,0}, vec3{0,0,-1} };
	static_assert(math::triangle<decltype(t)>);
	static_assert(math::plane<decltype(t)>);

	vec3 p0{0,0,0};
	assert(math::vertex<0>(t) == p0);
	vec3 p1{1,0,0};
	assert(math::vertex<1>(t) == p1);
	vec3 p2{0,0,-1};
	assert(math::vertex<2>(t) == p2);

	vec3 n{0,1,0};
	assert(math::normal(t) == n);
}