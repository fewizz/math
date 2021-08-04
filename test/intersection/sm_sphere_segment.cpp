#include "math/intersection/sm_sphere_segment.hpp"
#include "math/segment.hpp"
#include <glm/vec3.hpp>
#include <cassert>

int main() {
	math::sm_sphere_by_origin_direction_radius sph{
		glm::vec3{0}, glm::vec3{0,1,0}, 1.0
	};

	math::segment_by_point_direction_length seg {
		glm::vec3{10,10,0}, glm::vec3{-1,0,0}, 20
	};

	math::sm_sphere_segment_intersection i_center {sph, seg};

	assert(i_center.sphere_distance() == 9);
	assert(i_center.with_edge());

	sph.origin.x = -10.5F;
	math::sm_sphere_segment_intersection i_neg {sph, seg};

	assert(i_neg.with_vertex());

	sph.origin.x = -10.5F;
	math::sm_sphere_segment_intersection i_pos {sph, seg};

	assert(i_pos.with_vertex());
}