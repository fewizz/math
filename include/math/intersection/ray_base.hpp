#pragma once

#include "../ray.hpp"
#include <optional>
#include <cassert>

namespace math {

template<math::ray Ray, typename With, typename Dist = math::length_type<math::origin_type<Ray>>>
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
		return origin(ray) + direction(ray) * distance();
	}

	Dist distance() const {
		assert(result.has_value());
		return result.value();
	}

	/*glm::vec<3, T> normal() const {
		return make_normal_negative_to_direction(with.normal(), ray.direction());
	}*/
};

}