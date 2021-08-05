#pragma once

#include "sm_sphere_base.hpp"
#include "sm_sphere_ray.hpp"
#include "sm_sphere_point.hpp"

namespace math {

template<math::sm_sphere Sphere, math::segment Segment, typename Dist = math::common_element_type<math::origin_type<Sphere>>>
struct sm_sphere_segment_intersection : sm_sphere_intersection_base<Sphere, Segment, Dist> {
	enum type_t {
		edge, vertex
	} m_type;

	sm_sphere_segment_intersection(Sphere sph, Segment seg)
		: sm_sphere_intersection_base<Sphere, Segment, Dist>{ sph, seg }
	{
		auto i = math::sm_sphere_ray_intersection{ sph, seg };
	
		if(!i) return;

		if(i.ray_distance() < 0) {
			math::sm_sphere_point_intersection i0{ sph, math::vertex<0>(seg) };
			if(i0) {
				this->result = i0.sphere_distance();
				m_type = vertex;
				this->normal = i0.opposite_normal();
			}
		}
		else if(i.ray_distance() <= seg.length) {
			this->result = i.sphere_distance();
			m_type = edge;
			this->normal = i.opposite_normal();
		}
		else {
			math::sm_sphere_point_intersection i0{ sph, math::vertex<1>(seg) };
			if(i0) {
				this->result = i0.sphere_distance();
				m_type = vertex;
				this->normal = i0.opposite_normal();
			}
		}
	}

	type_t type() const {
		return m_type;
	}

	bool with_vertex() const {
		return m_type == vertex;
	}

	bool with_edge() const {
		return m_type == edge;
	}
};

}