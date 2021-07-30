#pragma once

#include "../ray.hpp"
#include <optional>

namespace math {

template<math::ray Ray, typename With, typename Dist>
struct ray_intersection_base {
protected:
	Ray ray;
	With with;
	std::optional<Dist> result;

	ray_intersection_base(Ray ray, With with, std::optional<Dist> result)
		: ray{ ray }, with{ with }, result{ result }
	{}

public:
	ray_intersection_base(const ray_intersection_base&) = default;

	explicit operator bool () const {
		return result.has_value();
	}

	auto position() const {
		return ray.origin() + ray.direction() * distance();
	}

	Dist distance() const {
		return result.value();
	}

	/*glm::vec<3, T> normal() const {
		return make_normal_negative_to_direction(with.normal(), ray.direction());
	}*/
};

}