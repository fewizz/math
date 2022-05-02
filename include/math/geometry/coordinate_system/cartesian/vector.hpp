#pragma once

#include <core/array.hpp>
#include <core/accumulate.hpp>
#include <core/transform.hpp>

#include "../../vector.hpp"
#include "../../../square_root.hpp"

namespace math::geometry::cartesian {

	template<typename Type, nuint Size>
	struct vector : math::geometry::vector_marker, array<Type, Size> {

		template<typename... Args>
		vector(Args&&... args) :
			array<Type, Size>{ forward<Args>(args)... }
		{}

		Type dot(const vector& other) const {
			Type result{};

			for(nuint i = 0; i < Size; ++i) {
				result += (*this)[i] * other[i];
			}

			return result;
		}

		Type length_square() const {
			return dot(*this);
		}

		Type length() const {
			return math::square_root(length_square());
		}

	};

	template<typename Type, nuint Size>
	vector<Type, Size> operator * (vector<Type, Size> v, Type s) {
		for(auto& e : v) e *= s; return v;
	}

	template<typename Type, nuint Size>
	vector<Type, Size> operator * (Type s, vector<Type, Size> v) {
		for(auto& e : v) e *= s; return v;
	}

}