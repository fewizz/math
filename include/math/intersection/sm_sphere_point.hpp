#pragma once

#include "sm_sphere_base.hpp"

namespace math {

template<math::sm_sphere Sphere, math::point Point, typename Dist = math::length_type<math::origin_type<Sphere>>>
struct sm_sphere_point_intersection : math::sm_sphere_intersection_base<Sphere, Point, Dist> {
	/*
	(S + Dt - P)₂ = r²
	(S + Dt)₂ - 2(S + Dt)·P + P₂ = r²
	S₂ + 2tS·D + t²D₂ - 2(S·P + Dt·P) + P₂ = r²
	S₂ + 2tS·D + t²D₂ - 2S·P - 2tD·P + P₂ - r² = 0

	a = D₂
	b = 2S·D - 2D·P
	c = S₂ - 2S·P + P₂ - r²
	*/
	sm_sphere_point_intersection(Sphere sphere, Point point)
		: sm_sphere_intersection_base<Sphere, Point, Dist>{ sphere, point, [&]() -> std::optional<Dist> {
			auto S = math::origin(sphere);
			auto P = point;
			auto D = math::direction(sphere);
			auto r = math::radius(sphere);

			Dist a = math::dot(D, D);
			Dist b = 2.0 * (math::dot(S, D) - math::dot(D, P));
			Dist c = math::dot(S, S) - 2.0 * math::dot(S, P) + math::dot(P, P) - r*r;

			Dist dis = b*b - 4.0*a*c;
			if(dis < 0) return {};
			return { (-b - std::sqrt(dis)) / (2.0 * a) };
		}() }
	{}
};

}