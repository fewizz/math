#include "math/intersection/ray_plane.hpp"
#include "glm/vec3.hpp"
#include "math/plane.hpp"
#include "math/ray.hpp"
#include <cassert>

int main() {
	using namespace math;
	using namespace glm;

	ray_plane_intersection i{
		ray_by_point_and_direction{ vec3{0.0F,0.0F,0.0F}, vec3{0.0F,1.0F,0.0F} },
		plane_by_normal_and_distance_to_center{ vec3{0.0F,-1.0F,0.0F}, 10.0F }
	};

	assert(i.distance() == 10.0F);
}