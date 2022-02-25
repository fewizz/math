#include "math/geometry/ray.hpp"
#include "math/geometry/ray/by_origin_and_direction.hpp"
#include "math/geometry/coordinate_system/cartesian/vector.hpp"
#include "math/geometry/coordinate_system/cartesian/direction.hpp"

int main() {
	math::geometry::ray_by_origin_and_direction<
		math::geometry::cartesian::vector<float, 3>,
		math::geometry::cartesian::direction<float, 3>
	> r{};

	static_assert(math::geometry::ray<decltype(r)>);
}