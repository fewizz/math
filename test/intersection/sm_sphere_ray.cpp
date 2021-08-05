#include "math/intersection/sm_sphere_ray.hpp"
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <cassert>

int main() {
	math::sm_sphere_ray_intersection i {
		math::sm_sphere_by_origin_direction_radius {
			glm::vec3{0}, glm::vec3{0,1,0}, 1.0
		},
		math::ray_by_point_and_direction {
			glm::vec3{10,10,0}, glm::vec3{-1,0,0}
		}
	};

	assert(i.sphere_distance() == 9);
	glm::vec3 pos{0,10,0};
	assert(i.position() == pos);
	assert(i.ray_distance() == 10);
}