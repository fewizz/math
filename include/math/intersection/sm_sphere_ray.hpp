#pragma once

#include "sm_sphere_intersection_base.hpp"
#include "../ray.hpp"

namespace math {

template<math::sm_sphere Sphere, math::ray Ray, typename Dist>
struct sm_sphere_ray_intersection : sm_sphere_intersection_base<Sphere, Ray, Dist> {
	/*
	(tL + D - yP)·(yP) = 0
	tyL·P + yD·P - y²P₂ = 0
	tL·P + D·P - yP₂ = 0
	y = (tL·P + D·P) / P₂

	(D - P*((tL·P + D·P) / P₂))₂ =
	D₂ - 2(tL·P + D·P)*D·P/P₂ + ((tL·P + D·P) / P₂)²P₂ =
	D₂ - 2tL·PD·P/P₂ - 2(D·P)²/P₂ + (tL·P + D·P)²/P₂ =
	D₂ - 2tL·PD·P/P₂ - 2(D·P)²/P₂ + (t²(L·P)² + 2tL·PD·P + (D·P)²)/P₂ =
	D₂ - 2tL·PD·P/P₂ - 2(D·P)²/P₂ + t²(L·P)²/P₂ + 2tL·PD·P/P₂ + (D·P)²/P₂ =
	D₂ - (D·P)²/P₂ + t²(L·P)²/P₂

	2tL·(D - P((tL·P + D·P) / P₂))
	2tL·(D - P(tL·P/P₂ + D·P/P₂))
	2tL·D - 2tL·P[tL·P/P₂ + D·P/P₂)]
	2tL·D - 2tL·[t(L·P/P₂)P + (D·P/P₂)P]
	2tL·D - 2t²(L·P)²/P₂ - 2tD·PL·P/P₂

	(tL + D - yP)₂ = r²
	(tL + D - P*((tL·P + D·P) / P₂))₂ = r²
	t²L₂ + 2tL·D - 2t²(L·P)²/P₂ - 2tD·PL·P/P₂ + D₂ - (D·P)²/P₂ + t²(L·P)²/P₂
	t²L₂ + 2tL·D - t²(L·P)²/P₂ - 2tD·PL·P/P₂ + D₂ - (D·P)²/P₂

	a = L₂ - (L·P)²/P₂
	b = 2L·D - 2D·PL·P/P₂
	c = D₂ - (D·P)²/P₂ - r²
	*/
	sm_sphere_ray_intersection(Sphere s, Ray r)
		: sm_sphere_intersection_base<Sphere, Ray, Dist>{ s, r, [&]() -> std::optional<Dist> {
			using namespace std;
			using namespace math;

			auto S = origin(s);
			auto R = origin(r);
			auto L = direction(s);
			auto P = direction(r);
			auto D = S - R;
			auto r = radius(s);

			auto LL = dot(L,L);
			auto PP = dot(P,P);
			auto LP = dot(L,P);
			auto DP = dot(D,P);

			Dist a = LL - LP*LP/PP;
			Dist b = 2.0*(dot(L,D) - DP* LP/PP);
			Dist c = dot(D,D) - DP*DP/PP - r*r;

			Dist dis = b*b - 4*a*c;
			if(dis < 0 || a == 0) return {};

			Dist t = (-b - sqrt(dis)) / (2.0*a);

			return { t };
		}() }
	{}

	auto position() const {
		return origin(this->with) + direction(this->with) * ray_distance();
	}

	Dist ray_distance() const {
		using namespace std;
		using namespace math;

		auto S = origin(this->sphere);
		auto R = origin(this->with);
		auto L = direction(this->sphere);
		auto P = direction(this->with);
		auto D = S - R;

		auto PP = dot(P,P);
		auto LP = dot(L,P);
		auto DP = dot(D,P);
		
		return (this->sphere_distance() * LP + DP) / PP;
	}

	auto normal() const {
		return (this->sphere_position() - position()) / radius(this->sphere);
	}
};

}