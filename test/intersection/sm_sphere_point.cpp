#include "math/intersection/sm_sphere_point.hpp"
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <cassert>

int main() {
	math::sm_sphere_point_intersection i {
		math::sm_sphere_by_origin_direction_radius {
			glm::vec3{0}, glm::vec3{0,1,0}, 1.0
		},
		glm::vec3{0,5,0}
	};

	assert(i.sphere_distance() == 4);
	glm::vec3 pos{0,5,0};
	assert(i.position() == pos);

}