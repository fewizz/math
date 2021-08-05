#include "math/intersection/sm_sphere_plane.hpp"
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <cassert>

int main() {
	math::sm_sphere_by_origin_direction_radius s{
		glm::vec3{0},
		glm::vec3{0,1,0},
		1
	};

	glm::vec3 pos{0, 10, 0};

	math::sm_sphere_plane_intersection i{
		s,
		math::plane_by_normal_and_distance_to_center {
			glm::vec3{0,-1,0}, 10.0F
		}
	};

	static_assert(std::is_same_v<math::common_element_type<decltype(i.position())>, float>);
	assert(i.sphere_distance() == 9.0);
	assert(i.position() == pos);


	return 0;
}