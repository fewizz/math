#include "math/segment.hpp"
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <cassert>
#include "math/origin.hpp"
#include "math/direction.hpp"

int main() {
	glm::vec3 o{0};
	glm::vec3 d{1,0,0};

	math::segment_by_point_direction_length s{o, d, 2.0F};
	static_assert(math::segment<decltype(s)>);

	assert(math::origin(s) == o);
	assert(math::direction(s) == d);
	assert(math::length(s) == 2);
	
}