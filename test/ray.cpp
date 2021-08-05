#include "math/ray.hpp"
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <cassert>

int main() {
	glm::vec3 o{0};
	glm::vec3 d{1,0,0};

	static_assert(math::point<decltype(o)>);
	static_assert(math::vector<decltype(d)>);
	
	math::ray_by_point_and_direction r{o, d};

	static_assert(math::ray<decltype(r)>);

	assert(math::origin(r) == o);
	assert(math::direction(r) == d);
}