#pragma once

#include <core/expected.hpp>

#include "../ray.hpp"

namespace math::geometry {

	template<math::geometry::ray Ray, typename With, typename Dist>
	struct ray_intersection_base {
	protected:
		Ray ray;
		With with;
		Dist result;
	
		ray_intersection_base(Ray ray, With with, std::optional<Dist> result)
			: ray{ ray }, with{ with }, result{ result }
		{}
	
	public:
		ray_intersection_base(const ray_intersection_base&) = default;
	
		auto position() const {
			return origin(ray) + direction(ray) * distance();
		}
	
		Dist distance() const {
			assert(result.has_value());
			return result.value();
		}
	
		auto opposite_normal() const {
			return math::turn_normal_opposite_to_direction(math::normal(with), math::direction(ray));
		}
	};

}