#include "math/intersection/ray_triangle.hpp"
#include "math/ray.hpp"
#include "math/triangle.hpp"
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <cassert>

int main() {
	math::ray_triangle_intersection i {
		math::ray_by_point_and_direction{ glm::vec3{0}, glm::vec3{0,1,0} },
		math::triangle_by_points {
			glm::vec3{ -1, 1,  1 },
			glm::vec3{  1, 1,  1 },
			glm::vec3{  0, 1, -1 }
		}
	};
	
	assert(i.distance() == 1.0F);
}