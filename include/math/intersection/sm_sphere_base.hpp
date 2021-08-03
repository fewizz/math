#pragma once

#include <optional>
#include "../sm_sphere.hpp"
#include "../sphere.hpp"
#include "../normal.hpp"
#include <cassert>

namespace math {

template<math::sm_sphere Sphere, typename With, typename Dist = math::length_type<math::origin_type<Sphere>>>
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
		return origin(sphere) + direction(sphere) * sphere_distance();
	}

	auto sphere_at_position() const {
		return math::sphere_by_point_radius{ sphere_position(), radius(sphere) };
	}

	Dist sphere_distance() const {
		assert(result.has_value());
		return result.value();
	}

	auto opposite_normal() const {
		if constexpr(math::point<With>) {
			return (sphere_position() - with) / radius(sphere);
		}
		else {
			return math::turn_normal_opposite_to_direction(math::normal(with), math::direction(sphere));
		}
	}

	auto position() const {
		return sphere_position() + ( -opposite_normal() * radius(sphere) );
	}
};

}