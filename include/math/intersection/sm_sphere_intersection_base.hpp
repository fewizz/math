#pragma once

#include <optional>
#include "../sm_sphere.hpp"
#include "../sphere.hpp"

namespace math {

template<math::sm_sphere Sphere, typename With, typename Dist>
struct sm_sphere_intersection_base {
protected:
	Sphere sphere;
	With with;
	std::optional<Dist> result;

	sm_sphere_intersection_base(Sphere sphere, With with, std::optional<Dist> result = {})
		: sphere{ sphere }, with{ with }, result{ result }
	{}

public:
	sm_sphere_intersection_base(const sm_sphere_intersection_base&) = default;

	explicit operator bool () const {
		return result.has_value();
	}

	auto sphere_position() const {
		return sphere.origin + sphere.direction * sphere_distance();
	}

	auto sphere_at_position() const {
		return math::sphere_by_point_radius{ sphere_position(), sphere.radius };
	}

	Dist sphere_distance() const {
		return result.value();
	}

	auto normal() const {
		//TODO//return make_normal_negative_to_direction(with.normal(), sphere.direction);
		return normal(with);
	}

	auto position() const {
		return sphere_position() + ( -normal() * sphere.radius );
	}
};

}