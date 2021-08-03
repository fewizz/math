#include "math/sm_sphere.hpp"
#include "glm/vec3.hpp"
#include <cassert>

int main() {
	math::sm_sphere_by_origin_direction_radius sm {
		glm::vec3{0}, glm::vec3(1,0,0), 1.0F
	};

	static_assert(math::sm_sphere<decltype(sm)>);

	assert(math::origin(sm) == glm::vec3(0));
	assert(math::direction(sm) == glm::vec3(1,0,0));
	assert(math::radius(sm) == 1.0F);

	return 0;
}