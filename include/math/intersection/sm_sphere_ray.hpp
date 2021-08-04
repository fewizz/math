#pragma once

#include "sm_sphere_base.hpp"
#include "../ray.hpp"

namespace math {

template<math::sm_sphere Sphere, math::ray Ray, typename Dist = math::length_type<math::origin_type<Sphere>>>
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
	sm_sphere_ray_intersection(Sphere s, Ray ray)
		: sm_sphere_intersection_base<Sphere, Ray, Dist>{ s, ray }
	{
		auto S = math::origin(s);
		auto R = math::origin(ray);
		auto L = math::direction(s);
		auto P = math::direction(ray);
		auto D = S - R;
		auto r = math::radius(s);

		auto LL = math::dot(L,L);
		auto PP = math::dot(P,P);
		auto LP = math::dot(L,P);
		auto DP = math::dot(D,P);

		Dist a = LL - LP*LP/PP;
		Dist b = 2.0*(math::dot(L,D) - DP* LP/PP);
		Dist c = math::dot(D,D) - DP*DP/PP - r*r;

		Dist dis = b*b - 4*a*c;
		if(dis < 0 || a == 0) return;

		Dist distance = (-b - std::sqrt(dis)) / (2.0*a);

		this->result = distance;
		this->normal = (this->sphere_position() - position()) / r;
	}

	auto position() const {
		return origin(this->with) + direction(this->with) * ray_distance();
	}

	Dist ray_distance() const {
		auto S = math::origin(this->sphere);
		auto R = math::origin(this->with);
		auto L = math::direction(this->sphere);
		auto P = math::direction(this->with);
		auto D = S - R;

		auto PP = math::dot(P,P);
		auto LP = math::dot(L,P);
		auto DP = math::dot(D,P);
		
		return (this->sphere_distance() * LP + DP) / PP;
	}
};

}