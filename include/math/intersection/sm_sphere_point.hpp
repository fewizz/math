#pragma once

#include "sm_sphere_base.hpp"

namespace math {

template<math::sm_sphere Sphere, math::point Point, typename Dist>
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
			using namespace std;
			using namespace math;

			auto S = origin(sphere);
			auto P = point;
			auto D = direction(sphere);
			auto r = radius(sphere);

			Dist a = dot(D, D);
			Dist b = 2.0 * (dot(S, D) - dot(D, P));
			Dist c = dot(S, S) - 2.0 * dot(S, P) + dot(P, P) - r*r;

			Dist dis = b*b - 4.0*a*c;
			if(dis < 0) return {};
			return { (-b - sqrt(dis)) / (2.0 * a) };
		}() }
	{}

	auto normal() const {
		return (this->sphere_position() - this->with) / radius(this->sphere);
	}
};

}